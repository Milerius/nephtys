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
        $<$<CXX_COMPILER_ID:GNU>:-static>
        $<$<CXX_COMPILER_ID:GNU>:stdc++fs>
        $<$<CXX_COMPILER_ID:Clang>:>)

##! Installation
if (LINUX)
    ##! Install
    install(TARGETS
            nephtys_server
            DESTINATION bin
            )

    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/org.nephtys.server.desktop
            DESTINATION share/applications/
    )

    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/org.nephtys.server.appdata.xml
            DESTINATION share/metainfo/
    )

    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/nephtys_icon.png
            DESTINATION share/icons/hicolor/128x128/apps
    )
endif ()