add_executable(nephtys_server)
target_sources(nephtys_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(nephtys_server CONAN_PKG::asio CONAN_PKG::jsonformoderncpp -static)