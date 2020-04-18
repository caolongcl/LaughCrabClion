aux_source_directory(. SRC_GLAD)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_library(glad SHARED ${SRC_GLAD})