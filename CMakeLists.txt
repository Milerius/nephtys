if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there")
endif ()

##! Configuration
cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(STRINGS "VERSION.md" VERSION_NB)
project(nepthys
        VERSION ${VERSION_NB}
        DESCRIPTION "Open-Source MMORPG Written in C++"
        LANGUAGES CXX)

##! CMake extras
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(nephtys)
init_nephtys()

##! Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS KEEP_RPATHS)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#init_rpath()

##! Generate version header
if (NOT EXISTS common/common/include/nephtys/version.hpp)
    configure_file(${CMAKE_MODULE_PATH}/version.hpp.in common/common/include/nephtys/version.hpp @ONLY)
endif ()

##! CMake Options
option(USE_ASAN "Use address sanitizer" OFF)
option(USE_TSAN "Use thread sanitizer" OFF)
option(USE_UBSAN "Use thread sanitizer" OFF)
option(USE_CONAN_HELPERS "enable auto conan detection during generation of CMake" OFF)
if (LINUX)
    option(AUTO_BUILD_APPIMAGE "Enable it to autobuild appimage" OFF)
endif ()

add_subdirectory(cmake/targets)
add_subdirectory(vendor/loguru)
##! Sub-Projects
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(launcher)
