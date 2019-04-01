if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there")
endif ()

##! Configuration
cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

##! Project
project(nepthys)

##! Sub-Projects
add_subdirectory(client)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

if (LINUX)
    add_subdirectory(server)
endif ()