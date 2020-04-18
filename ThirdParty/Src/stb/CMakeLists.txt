aux_source_directory(. SRC_STB)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_library(stb SHARED ${SRC_STB})