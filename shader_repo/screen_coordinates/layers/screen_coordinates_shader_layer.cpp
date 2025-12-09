// copyright 2025 swaroop.

#include "screen_coordinates_shader_layer.h"

ScreenCoordinatesShaderLayer::ScreenCoordinatesShaderLayer(EngineObject* parent)
    : DefaultShaderLayer(
        parent,
        "ScreenCoordinatesShaderLayer",
        "shader_repo/screen_coordinates/shaders/screen_coordinates.vert.spv",
        "shader_repo/screen_coordinates/shaders/screen_coordinates.frag.spv")
{

}