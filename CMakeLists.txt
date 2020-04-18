cmake_minimum_required(VERSION 3.10)
project(LaughCrab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

include_directories(Test)
include_directories(Code/Core)
include_directories(Code/Core/Math)
include_directories(Code/Core/Memory)
include_directories(Code/Core/Service)
include_directories(Code/Core/Utils)
include_directories(Code/Include)
include_directories(ThirdParty/Include/Glad)
include_directories(ThirdParty/Include/Glm)
include_directories(ThirdParty/Include/OpenGex)
include_directories(ThirdParty/Include/SDL)
include_directories(ThirdParty/Include/stb)

aux_source_directory(. SRC_MAIN)
aux_source_directory(./Test SRC_TEST)

add_subdirectory(Code/Core)
add_subdirectory(Test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(ThirdParty/Src/Glad)
#add_subdirectory(ThirdParty/Src/OpenGex)
add_subdirectory(ThirdParty/Src/stb)

link_directories(ThirdParty/Libs)

add_executable(LaughCrab ${SRC_MAIN} ${SRC_TEST})

target_link_libraries(LaughCrab core)


