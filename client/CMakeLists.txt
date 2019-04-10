################################### nephtys_client_shared_deps
add_library(nephtys_client_shared_deps INTERFACE)

target_link_libraries(nephtys_client_shared_deps INTERFACE
        CONAN_PKG::sfml CONAN_PKG::entt CONAN_PKG::jsonformoderncpp CONAN_PKG::doom_strong_types
        $<$<CXX_COMPILER_ID:GNU>:-static-libstdc++>
        $<$<CXX_COMPILER_ID:GNU>:stdc++fs>
        $<$<CXX_COMPILER_ID:Clang>:>)
target_sources(nephtys_client_shared_deps INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/config/config.cpp
        $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/src/resources/details/linux/app_image_real_path.cpp>)

target_compile_options(nephtys_client_shared_deps INTERFACE
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /FS /DEBUG /Od /MP /MDd /Oy- /W4 /permissive- /std:c++latest>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 -DNDEBUG /MP /W4 /permissive- /std:c++latest>)

target_include_directories(nephtys_client_shared_deps INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/common/include)

if (USE_ASAN)
    message("-- ASAN Enabled, Configuring...")
    target_compile_options(nephtys_client_shared_deps INTERFACE
            $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=address -fno-omit-frame-pointer>)
    target_link_options(nephtys_client_shared_deps INTERFACE
            $<$<AND:$<CONFIG:Debug>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fsanitize=address -fno-omit-frame-pointer>)
endif ()

################################### nephtys_client
add_executable(nephtys_client)
target_sources(nephtys_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(nephtys_client PRIVATE nephtys_client_shared_deps)
if (LINUX)
    get_target_property(nephtys_client_runtime_directory nephtys_client RUNTIME_OUTPUT_DIRECTORY)
    set_target_properties(nephtys_client PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/bin)
    message("runtime_directory nephtys_client: ${nephtys_client_runtime_directory}")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/config/game_config.json
            ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/share/assets/config/game_config.json COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/linux/org.nephtys.client.desktop
            ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/share/applications/org.nephtys.client.desktop COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/linux/org.nephtys.client.appdata.xml
            ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/share/metainfo/org.nephtys.client.appdata.xml COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/linux/nephtys_icon.png
            ${nephtys_client_runtime_directory}/NephtysClientAppDir/usr/share/icons/hicolor/128x128/apps/nephtys_icon.png COPYONLY)
    if (AUTO_BUILD_APPIMAGE)
        add_custom_command(TARGET nephtys_client
                POST_BUILD COMMAND
                bash -c
                "${PROJECT_SOURCE_DIR}/tools/linux/linuxdeploy-x86_64.AppImage --appdir ${nephtys_client_runtime_directory}/NephtysClientAppDir --output appimage"
                $<TARGET_FILE:nephtys_client>
                WORKING_DIRECTORY ${nephtys_client_runtime_directory})
    endif ()
endif ()
########################################################################

##! Test
add_executable(nephtys-client-test)
target_sources(nephtys-client-test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/config/config.test.cpp
        $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/src/resources/details/linux/app_image_real_path.test.cpp>
        )
target_link_libraries(nephtys-client-test PRIVATE CONAN_PKG::doctest PRIVATE nephtys_client_shared_deps)

if (NEPHTYS_COVERAGE)
    target_compile_options(nephtys-client-test PUBLIC --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(nephtys-client-test PUBLIC --coverage -fprofile-arcs -ftest-coverage)
endif ()