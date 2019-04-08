set(ICON)
if (APPLE)
    find_library(NOESIS_LIBRARY
            Noesis.dylib
            HINTS
            ${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/osx/)

    find_library(NOESISAPP_LIBRARY
            NoesisApp.dylib
            HINTS
            ${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/osx/)
    set(ICON assets/osx/nephtys_launcher.icns)
    set_source_files_properties(glfw.icns PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")
endif ()

add_executable(nephtys_launcher MACOSX_BUNDLE ${ICON})

target_sources(nephtys_launcher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_compile_options(nephtys_launcher PUBLIC
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /FS /DEBUG /Od /MP /MDd /Oy- /W4 /permissive- /std:c++latest>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 -DNDEBUG /MP /W4 /permissive- /std:c++latest>)


target_link_libraries(nephtys_launcher PRIVATE CONAN_PKG::sfml
        $<$<CXX_COMPILER_ID:GNU>:-static>
        $<$<CXX_COMPILER_ID:GNU>:stdc++fs>
        $<$<PLATFORM_ID:Darwin>:${NOESIS_LIBRARY}>
        $<$<PLATFORM_ID:Darwin>:${NOESISAPP_LIBRARY}>)

target_include_directories(nephtys_launcher PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/common/include
        ${PROJECT_SOURCE_DIR}/vendor/noesisgui/include)

if (APPLE)
    set_target_properties(nephtys_launcher PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "nephtys_launcher"
            RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/assets/osx/nephtys_launcher.icns
            MACOSX_BUNDLE_SHORT_VERSION_STRING 0.0.1
            MACOSX_BUNDLE_LONG_VERSION_STRING 0.0.1
            MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/cmake/MacOSXBundleInfo.plist.in")
    configure_file(${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/osx/Noesis.dylib
            ${CMAKE_BINARY_DIR}/bin/nephtys_launcher.app/Contents/Frameworks/Noesis.dylib COPYONLY)
    configure_file(${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/osx/NoesisApp.dylib
            ${CMAKE_BINARY_DIR}/bin/nephtys_launcher.app/Contents/Frameworks/NoesisApp.dylib COPYONLY)
    add_custom_command(TARGET nephtys_launcher
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/"
            $<TARGET_FILE:nephtys_launcher>)
endif ()