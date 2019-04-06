add_executable(nephtys_client)

set(nephtys_client_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/config/config.cpp
        $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/src/resources/details/linux/app_image_real_path.cpp>
        )

target_sources(nephtys_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_compile_options(nephtys_client PUBLIC
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /FS /DEBUG /Od /MP /MDd /Oy- /W4 /permissive- /std:c++latest>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 -DNDEBUG /MP /W4 /permissive- /std:c++latest>)
target_link_libraries(nephtys_client PRIVATE CONAN_PKG::sfml CONAN_PKG::entt CONAN_PKG::jsonformoderncpp CONAN_PKG::doom_strong_types
        $<$<CXX_COMPILER_ID:GNU>:-static>
        $<$<CXX_COMPILER_ID:GNU>:stdc++fs>
        $<$<CXX_COMPILER_ID:Clang>:-static>)
target_include_directories(nephtys_client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/common/include)

##Properties
get_target_property(nephtys_client_libraries nephtys_client LINK_LIBRARIES)
get_target_property(nephtys_client_output_directory nephtys_client RUNTIME_OUTPUT_DIRECTORY)
get_target_property(nephtys_client_include_directories nephtys_client INCLUDE_DIRECTORIES)

##! Test
add_executable(nephtys-client-test)
target_sources(nephtys-client-test PUBLIC
        ${nephtys_client_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/config/config.test.cpp
        $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/src/resources/details/linux/app_image_real_path.test.cpp>)
target_link_libraries(nephtys-client-test PRIVATE CONAN_PKG::doctest ${nephtys_client_libraries})
target_include_directories(nephtys-client-test PRIVATE ${nephtys_client_include_directories})
if (NEPHTYS_COVERAGE)
    target_compile_options(nephtys-client-test PUBLIC --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(nephtys-client-test PUBLIC --coverage -fprofile-arcs -ftest-coverage)
endif ()

##! Config file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/config/game_config.json
        ${nephtys_client_output_directory}/share/assets/config/game_config.json COPYONLY)

if (LINUX)
    ##! Install
    install(TARGETS
            nephtys_client
            DESTINATION bin
            )

    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/nephtys.desktop
            DESTINATION share/applications/
    )

    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/config/game_config.json
            DESTINATION share/assets/config/
    )

    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/nephtys_icon.png
            DESTINATION share/icons/hicolor/128x128/apps
    )
endif ()