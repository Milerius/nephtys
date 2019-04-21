##! SFML-COMMON
add_library(nephtys-sfml-common-shared-deps INTERFACE)
target_link_libraries(nephtys-sfml-common-shared-deps INTERFACE
        nephtys::common
        nephtys::default_settings
        CONAN_PKG::sfml)
target_include_directories(nephtys-sfml-common-shared-deps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(nephtys::sfml::common ALIAS nephtys-sfml-common-shared-deps)

##! Graphics
add_library(nephtys-sfml-graphics-shared-deps INTERFACE)
target_link_libraries(nephtys-sfml-graphics-shared-deps INTERFACE
        CONAN_PKG::entt
        CONAN_PKG::doom_strong_types
        nephtys::sfml::common
        )
target_sources(nephtys-sfml-graphics-shared-deps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/sfml.graphics.cpp)
add_library(nephtys::sfml::graphics ALIAS nephtys-sfml-graphics-shared-deps)

##! Graphics test
add_executable(nephtys-sfml-graphics-test)
target_sources(nephtys-sfml-graphics-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.sfml.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/sfml.graphics.test.cpp)
target_link_libraries(nephtys-sfml-graphics-test PUBLIC CONAN_PKG::doctest nephtys::sfml::graphics)
target_enable_asan(nephtys-sfml-graphics-test)
target_enable_ubsan(nephtys-sfml-graphics-test)
target_enable_tsan(nephtys-sfml-graphics-test)
target_enable_coverage(nephtys-sfml-graphics-test)

##! Input
add_library(nephtys-sfml-input-shared-deps INTERFACE)
target_link_libraries(nephtys-sfml-input-shared-deps INTERFACE nephtys::sfml::graphics)
target_sources(nephtys-sfml-input-shared-deps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/input/sfml.input.cpp)
add_library(nephtys::sfml::input ALIAS nephtys-sfml-input-shared-deps)

##! Input test
add_executable(nephtys-sfml-input-test)
target_sources(nephtys-sfml-input-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.sfml.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/input/sfml.input.test.cpp)
target_link_libraries(nephtys-sfml-input-test PUBLIC CONAN_PKG::doctest nephtys::sfml::input)
target_enable_asan(nephtys-sfml-input-test)
target_enable_ubsan(nephtys-sfml-input-test)
target_enable_tsan(nephtys-sfml-input-test)
target_enable_coverage(nephtys-sfml-input-test)

##! All SFML Libraries
add_library(nephtys-sfml INTERFACE)
target_link_libraries(nephtys-sfml INTERFACE nephtys::sfml::graphics nephtys::sfml::input)
add_library(nephtys::sfml ALIAS nephtys-sfml)

