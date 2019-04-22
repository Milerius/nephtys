##! copy directory
if (APPLE)
    file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Resources/)
elseif (LINUX)
    file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../share/)
else ()
    file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
endif ()

################################### nephtys_client_shared_deps
add_library(nephtys_client_shared_deps INTERFACE)
target_compile_features(nephtys_client_shared_deps INTERFACE cxx_std_17)

target_link_libraries(nephtys_client_shared_deps INTERFACE
        CONAN_PKG::jsonformoderncpp
        CONAN_PKG::doom_strong_types
        nephtys::timer
        nephtys::default_settings
        nephtys::common
        nephtys::resources
        nephtys::sfml
        $<$<CXX_COMPILER_ID:GNU>:-static-libstdc++>)

target_include_directories(nephtys_client_shared_deps INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )


target_enable_asan(nephtys_client_shared_deps)
target_enable_tsan(nephtys_client_shared_deps)
target_enable_ubsan(nephtys_client_shared_deps)

################################### nephtys_client
add_executable(nephtys_client)
target_sources(nephtys_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(nephtys_client PUBLIC nephtys_client_shared_deps)
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
                "VERSION=${PROJECT_VERSION} ${PROJECT_SOURCE_DIR}/tools/linux/linuxdeploy-x86_64.AppImage --appdir ${nephtys_client_runtime_directory}/NephtysClientAppDir --output appimage"
                $<TARGET_FILE:nephtys_client>
                WORKING_DIRECTORY ${nephtys_client_runtime_directory})
    endif ()
endif ()
########################################################################

##! Test
add_executable(nephtys-client-test)
target_sources(nephtys-client-test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.client.cpp
        )
target_link_libraries(nephtys-client-test PRIVATE CONAN_PKG::doctest PUBLIC nephtys_client_shared_deps)
target_enable_coverage(nephtys-client-test)