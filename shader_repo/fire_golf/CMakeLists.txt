cmake_minimum_required(VERSION 3.20)
project(SHAD_fire_golf)

# Define the library and its sources
add_library(${PROJECT_NAME} STATIC
        fire_golf.cpp
        fire_golf.h
        layers/fire_golf_ui_layer.cpp
        layers/screen_coordinates_ui_layer.h
        layers/fire_golf_shader_layer.cpp
        layers/fire_golf_shader_layer.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/layers
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        shader_engine_interface
        select_menu
        Vulkan::Vulkan
        imgui
)