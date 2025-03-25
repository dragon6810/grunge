cmake_minimum_required(VERSION 3.0)
project(grunge C)

set(CMAKE_C_COMPILER emcc)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

file(GLOB_RECURSE SOURCES_LIST "src/*.c")
add_executable(grunge ${SOURCES_LIST})
include_directories(grunge "src")

set_target_properties(grunge PROPERTIES
    LINK_FLAGS "-sEXPORTED_FUNCTIONS=['_main'] -sEXPORTED_RUNTIME_METHODS=[] -sALLOW_MEMORY_GROWTH=1 -sNO_EXIT_RUNTIME=1 --js-library ${CMAKE_SOURCE_DIR}/library.js"
)