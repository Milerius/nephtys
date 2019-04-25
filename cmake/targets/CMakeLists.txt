add_library(error_settings INTERFACE)

# Using namespaces causes CMake to error our in case of typos on the
# consuming side, very important.
add_library(nephtys::error_settings ALIAS error_settings)

target_compile_options(
        error_settings
        INTERFACE
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wfatal-errors>
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wfatal-errors>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)


add_library(defaults_features INTERFACE)
add_library(nephtys::defaults_features ALIAS defaults_features)
target_compile_features(defaults_features INTERFACE cxx_std_17)

add_library(optimize_settings INTERFACE)

add_library(nephtys::optimize_settings ALIAS optimize_settings)

##! Msvc flags info
# /Zi - Produces a program database (PDB) that contains type information and symbolic debugging information for use with the debugger.
# /FS - Allows multiple cl.exe processes to write to the same .pdb file
# /DEBUG - Enable debug during linking
# /Od - Disables optimization
# /Ox - Full optimization
# /Oy- do not suppress frame pointers (recommended for debugging)

target_compile_options(optimize_settings INTERFACE
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang>>:-O2 -march=native>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O2 -march=native -pipe>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-O0 -g -pipe>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-O0 -g>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /FS /DEBUG /Od /MP /MDd /Oy->
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 -DNDEBUG /MP>
        )

add_library(default_settings INTERFACE)
add_library(nephtys::default_settings ALIAS default_settings)
target_link_libraries(default_settings INTERFACE nephtys::error_settings nephtys::optimize_settings nephtys::defaults_features)

add_library(noesis SHARED IMPORTED)
if (APPLE)
    set_target_properties(noesis PROPERTIES
            IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/osx/Noesis.dylib
            IMPORTED_GLOBAL TRUE)
elseif (WIN32)
    set_target_properties(noesis PROPERTIES
            IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/win64/Noesis.dll
            IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/vendor/noesisgui/lib/win64/Noesis.lib
            IMPORTED_GLOBAL TRUE)
else ()
    set_target_properties(noesis PROPERTIES
            IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/linux/libNoesis.so
            IMPORTED_GLOBAL TRUE)
endif ()
add_library(nephtys::noesis ALIAS noesis)


##! Doom meta
include(FetchContent)
#FetchContent_Declare(
#        doom_meta
#        GIT_REPOSITORY https://github.com/doom/meta.git
#        GIT_TAG 1.0.1
#)

FetchContent_Populate(
        doom_meta
        URL https://github.com/doom/meta/archive/1.0.1.tar.gz
        URL_HASH SHA256=398862d6dac8e1139f87965c9d085013b6b29b75372a517093b1924b63eee1dc
        SOURCE_DIR doom_meta
)
#FetchContent_MakeAvailable(doom_meta)

FetchContent_GetProperties(doom_meta)
if(NOT doom_meta_POPULATED)
    add_subdirectory(${doom_meta_SOURCE_DIR} ${doom_meta_BINARY_DIR})
endif()