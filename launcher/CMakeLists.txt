set(ICON)
configure_icon_osx(data/osx/nephtys_launcher.icns ICON nephtys_launcher.icns)

add_executable(nephtys_launcher MACOSX_BUNDLE ${ICON})

target_sources(nephtys_launcher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(nephtys_launcher
        PRIVATE CONAN_PKG::sfml
        PUBLIC
        nephtys::default_settings
        nephtys::common
        $<$<CXX_COMPILER_ID:GNU>:-static-libstdc++>
        PRIVATE
        nephtys::noesis)

target_include_directories(nephtys_launcher PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/vendor/noesisgui/include)

if (APPLE)
    include(data/osx/nephtys_launcher_install.cmake)
endif ()