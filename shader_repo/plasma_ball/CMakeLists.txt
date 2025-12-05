cmake_minimum_required(VERSION 4.0)
project(plasma_shader)

add_library(plasma_shader SHARED plasma.cpp)

target_link_libraries(plasma_shader PRIVATE EngineAPI)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shader_repo")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shader_repo")