add_library(nephtys-common INTERFACE)
target_include_directories(nephtys-common INTERFACE include)
target_link_libraries(nephtys-common INTERFACE
        CONAN_PKG::doom_strong_types
        nephtys::loguru
        $<$<PLATFORM_ID:Linux>:stdc++fs>
        $<$<PLATFORM_ID:Darwin>:c++fs>)
add_library(nephtys::common ALIAS nephtys-common)


add_library(nephtys-timer INTERFACE)
target_link_libraries(nephtys-timer INTERFACE nephtys::common)
target_sources(nephtys-timer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/timer/timestep.cpp)
add_library(nephtys::timer ALIAS nephtys-timer)


add_executable(nephtys-common-test)
target_sources(nephtys-common-test PRIVATE src/version.test.cpp test/test.common.cpp src/timer/timestep.test.cpp)
target_link_libraries(nephtys-common-test PRIVATE CONAN_PKG::doctest nephtys::default_settings nephtys::timer)

target_include_directories(nephtys-common-test PUBLIC
        include)

target_enable_asan(nephtys-common-test)
target_enable_tsan(nephtys-common-test)
target_enable_ubsan(nephtys-common-test)
target_enable_coverage(nephtys-common-test)