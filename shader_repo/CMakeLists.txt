cmake_minimum_required(VERSION 3.20)
project(vk_shader_repo)

find_package(Vulkan REQUIRED)

add_library(shader_engine_interface INTERFACE
        select_menu/select_menu.cpp
        select_menu/select_menu.h)
target_include_directories(shader_engine_interface INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../external"
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(shader_engine_interface INTERFACE Vulkan::Headers)




add_subdirectory(select_menu)

add_library(vk_shader_repo INTERFACE)
target_link_libraries(vk_shader_repo INTERFACE
        select_menu
)

target_include_directories(vk_shader_repo INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)