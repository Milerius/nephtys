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

macro(init_env)
    if (UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif ()
    if (APPLE)
        ##! For user that's install llvm through brew.
        link_directories("/usr/local/opt/llvm/lib")
    endif ()
endmacro()

macro(exec_conan)
    if (NOT EXISTS conanbuildinfo.cmake)
        if (USE_CONAN_HELPERS)
            message("Conan need to be executed")
            message("Conan installing remote ...")
            execute_process(COMMAND conan config install ../.conan/
                    RESULT_VARIABLE CMD_ERROR
                    OUTPUT_FILE CMD_OUTPUT)
            file(READ "${CMAKE_CURRENT_BINARY_DIR}/CMD_OUTPUT" OUTPUT)
            message("Conan adding remote output: ${OUTPUT}")
            execute_process(COMMAND conan install ../
                    RESULT_VARIABLE CMD_ERROR
                    OUTPUT_FILE CMD_OUTPUT)
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