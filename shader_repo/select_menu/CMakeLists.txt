cmake_minimum_required(VERSION 3.20)
project(select_menu)

add_library(${PROJECT_NAME} STATIC
        select_menu.cpp
        select_menu.h
        select_menu_layer.cpp
        select_menu_layer.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        shader_engine_interface
        SHAD_plasma_ball
        SHAD_screen_coordinates
)

