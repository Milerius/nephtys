add_library(nephtys-sfml-graphics-shared-deps INTERFACE)
target_include_directories(nephtys-sfml-graphics-shared-deps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(nephtys-sfml-graphics-shared-deps INTERFACE
        CONAN_PKG::entt
        CONAN_PKG::sfml
        CONAN_PKG::doom_strong_types
        nephtys::common
        nephtys::default_settings)
target_sources(nephtys-sfml-graphics-shared-deps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/sfml.graphics.cpp)

add_library(nephtys-sfml-graphics OBJECT)
target_link_libraries(nephtys-sfml-graphics PUBLIC nephtys-sfml-graphics-shared-deps)
add_library(nephtys::sfml-graphics ALIAS nephtys-sfml-graphics)

add_executable(nephtys-sfml-graphics-test)
target_sources(nephtys-sfml-graphics-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.sfml.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/sfml.graphics.test.cpp)
target_link_libraries(nephtys-sfml-graphics-test PRIVATE CONAN_PKG::doctest nephtys-sfml-graphics-shared-deps)

