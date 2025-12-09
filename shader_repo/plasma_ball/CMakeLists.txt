cmake_minimum_required(VERSION 3.20)
project(SHAD_plasma_ball)

# Define the library and its sources
add_library(${PROJECT_NAME} STATIC
        plasma_ball.cpp
        plasma_ball.h
        layers/plasma_ball_ui_layer.cpp
        layers/screen_coordinates_ui_layer.h
        layers/plasma_ball_shader_layer.cpp
        layers/plasma_ball_shader_layer.h
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