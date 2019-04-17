add_executable(nephtys-common-test)
target_sources(nephtys-common-test PRIVATE src/version.test.cpp test/test.common.cpp)
target_link_libraries(nephtys-common-test PRIVATE CONAN_PKG::doctest nephtys::default_settings)

target_include_directories(nephtys-common-test PUBLIC
        ${PROJECT_SOURCE_DIR}/common/include)

target_enable_asan(nephtys-common-test)
target_enable_tsan(nephtys-common-test)
target_enable_ubsan(nephtys-common-test)
target_enable_coverage(nephtys-common-test)