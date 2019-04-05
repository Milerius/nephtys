add_executable(nephtys_client)

target_sources(nephtys_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_compile_options(nephtys_client PUBLIC
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O2 -march=native -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-O0 -g -Wall -Wextra -Wfatal-errors>
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /FS /DEBUG /Od /MP /MDd /Oy- /W4 /permissive- /std:c++latest>
        $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2 -DNDEBUG /MP /W4 /permissive- /std:c++latest>)
