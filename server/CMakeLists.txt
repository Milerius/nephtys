add_executable(nephtys_server)

##! Sources
target_sources(nephtys_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

##! Compiler Warning/Options
target_compile_options(nephtys_server PUBLIC
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /FS /DEBUG /Od /MP /MDd /Oy- /W4 /permissive- /std:c++latest>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 -DNDEBUG /MP /W4 /permissive- /std:c++latest>)

##! Libraries
target_link_libraries(nephtys_server CONAN_PKG::asio CONAN_PKG::jsonformoderncpp
        $<$<CXX_COMPILER_ID:GNU>:-static-libstdc++>
        $<$<CXX_COMPILER_ID:GNU>:stdc++fs>
        $<$<CXX_COMPILER_ID:Clang>:>)


if (LINUX)
    get_target_property(nephtys_server_runtime_directory nephtys_server RUNTIME_OUTPUT_DIRECTORY)
    set_target_properties(nephtys_server PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${nephtys_server_runtime_directory}/NephtysServerAppDir/usr/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${nephtys_server_runtime_directory}/NephtysServerAppDir/usr/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${nephtys_server_runtime_directory}/NephtysServerAppDir/usr/bin)
    message("runtime_directory nephtys_server: ${nephtys_server_runtime_directory}")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/linux/org.nephtys.server.desktop
            ${nephtys_server_runtime_directory}/NephtysServerAppDir/usr/share/applications/org.nephtys.server.desktop COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/linux/org.nephtys.server.appdata.xml
            ${nephtys_server_runtime_directory}/NephtysServerAppDir/usr/share/metainfo/org.nephtys.server.appdata.xml COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/linux/nephtys_icon.png
            ${nephtys_server_runtime_directory}/NephtysServerAppDir/usr/share/icons/hicolor/128x128/apps/nephtys_icon.png COPYONLY)
    if (AUTO_BUILD_APPIMAGE)
        add_custom_command(TARGET nephtys_server
                POST_BUILD COMMAND
                bash -c
                "${PROJECT_SOURCE_DIR}/tools/linux/linuxdeploy-x86_64.AppImage --appdir ${nephtys_server_runtime_directory}/NephtysServerAppDir --output appimage"
                $<TARGET_FILE:nephtys_server>
                WORKING_DIRECTORY ${nephtys_server_runtime_directory})
    endif ()
endif ()