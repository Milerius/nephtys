add_executable(nephtys_server)

##! Sources
target_sources(nephtys_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

##! Libraries
target_link_libraries(nephtys_server
        PRIVATE
        CONAN_PKG::asio
        CONAN_PKG::jsonformoderncpp
        PUBLIC
        nephtys::default_settings
        nephtys::common
        $<$<CXX_COMPILER_ID:GNU>:-static-libstdc++>
        )

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