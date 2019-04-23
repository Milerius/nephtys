macro(configure_icon_osx icon_path icon_variable icon_name)
    if (APPLE)
        set(${icon_variable} ${icon_path})
        set_source_files_properties(${icon_name} PROPERTIES
                MACOSX_PACKAGE_LOCATION "Resources")
    endif ()
endmacro()

macro(target_enable_asan target)
    if (USE_ASAN)
        message("-- ASAN Enabled, Configuring...")
        target_compile_options(${target} INTERFACE
                $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=address -fno-omit-frame-pointer>)
        target_link_options(${target} INTERFACE
                $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=address -fno-omit-frame-pointer>)
    endif ()
endmacro()


macro(target_enable_tsan target)
    if (USE_TSAN AND NOT ASAN)
        message("-- TSAN Enabled, Configuring...")
        target_compile_options(${target} INTERFACE
                $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=thread -fno-omit-frame-pointer>)
        target_link_options(${target} INTERFACE
                $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=thread -fno-omit-frame-pointer>)
    endif ()
endmacro()

macro(target_enable_ubsan target)
    if (USE_UBSAN AND NOT ASAN)
        message("-- UBSAN Enabled, Configuring...")
        target_compile_options(${target} INTERFACE
                $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=undefined -fno-omit-frame-pointer>)
        target_link_options(${target} INTERFACE
                $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=undefined -fno-omit-frame-pointer>)
    endif ()
endmacro()

macro(target_enable_coverage target)
    if (NEPHTYS_COVERAGE)
        target_compile_options(${target} PUBLIC $<$<CXX_COMPILER_ID:GNU>:--coverage> -fprofile-arcs -ftest-coverage)
        target_link_options(${target} PUBLIC $<$<CXX_COMPILER_ID:GNU>:--coverage> -fprofile-arcs -ftest-coverage)
    endif ()
endmacro()

macro(download_app_image)
    if (LINUX)
        ## We need appimage
        if (NOT EXISTS ${PROJECT_SOURCE_DIR}/tools/linux/linuxdeploy-x86_64.AppImage)
            file(DOWNLOAD
                    https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
                    ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage
                    SHOW_PROGRESS
                    )
        endif ()
        if (EXISTS ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage)
            file(COPY
                    ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage DESTINATION
                    ${PROJECT_SOURCE_DIR}/tools/linux/
                    FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
        endif ()
        if (EXISTS ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage)
            file(REMOVE ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage)
        endif ()
    endif ()
endmacro()

macro(init_rpath)
    if (APPLE)
        set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
    elseif (LINUX)
        set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
    endif ()

    if (UNIX)
        set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
    endif ()
endmacro()


##! extra opti
macro(target_ipo tgt)
    check_ipo_supported(RESULT result OUTPUT output)
    if (result)
        message(STATUS "IPO / LTO enabled")
        set_target_properties(${tgt} PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    else ()
        message(STATUS "IPO / LTO not supported: <${output}>")
    endif ()
endmacro()

macro(init_env)
    include(CheckIPOSupported)
    if (UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif ()
    if (APPLE)
        ##! For user that's install llvm through brew.
        link_directories("/usr/local/opt/llvm/lib")
    endif ()
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(nephtys_compiler clang)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(nephtys_compiler gcc)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(nephtys_compiler msvc)
    endif ()
endmacro()

macro(nephtys_split_version VERSION_STRING MAJOR MINOR)
    #make a list from the version string
    string(REPLACE "." ";" VERSION_LIST "${VERSION_STRING}")

    #write output values
    list(LENGTH VERSION_LIST _version_len)
    list(GET VERSION_LIST 0 ${MAJOR})
    if (${_version_len} GREATER 1)
        list(GET VERSION_LIST 1 ${MINOR})
    endif ()
endmacro()

macro(exec_conan)
    if (NOT EXISTS conanbuildinfo.cmake)
        if (USE_CONAN_HELPERS)
            message("Conan need to be executed")
            message("Conan installing remote ...")
            execute_process(COMMAND conan config install ../.conan/remotes
                    RESULT_VARIABLE CMD_ERROR
                    OUTPUT_FILE CMD_OUTPUT)
            file(READ "${CMAKE_CURRENT_BINARY_DIR}/CMD_OUTPUT" OUTPUT)
            message("Conan adding remote output: ${OUTPUT}")
            if (APPLE)
                execute_process(COMMAND conan install --build missing ../.conan/osx
                        RESULT_VARIABLE CMD_ERROR
                        OUTPUT_FILE CMD_OUTPUT)
            elseif (LINUX)
                nephtys_split_version(${CMAKE_CXX_COMPILER_VERSION} VERSION_MAJOR VERSION_MINOR)
                execute_process(COMMAND conan install --build missing ../.conan/linux -s compiler=${nephtys_compiler} -s compiler.version=${VERSION_MAJOR} -s compiler.libcxx=libstdc++11
                        RESULT_VARIABLE CMD_ERROR
                        OUTPUT_FILE CMD_OUTPUT)
            else ()
                execute_process(COMMAND conan install --build missing ../.conan/windows
                        RESULT_VARIABLE CMD_ERROR
                        OUTPUT_FILE CMD_OUTPUT)
            endif ()
            file(READ "${CMAKE_CURRENT_BINARY_DIR}/CMD_OUTPUT" OUTPUT)
            message("Conan install output: ${OUTPUT}")

            MESSAGE(STATUS "CMD_ERROR:" ${CMD_ERROR})
            MESSAGE(STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})
        else ()
            MESSAGE(FATAL_ERROR "You need to execute conan install ../ or enable USE_CONAN_HELPERS in the root CMakeLists.txt")
        endif ()
    else ()
        message("Conan doesn't need to be executed")
    endif ()
endmacro()

macro(init_nephtys)
    init_env()
    exec_conan()
    download_app_image()
endmacro()