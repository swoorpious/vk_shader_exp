// copyright 2025 swaroop.

#include "fire_golf_shader_layer.h"

FireGolfShaderLayer::FireGolfShaderLayer(EngineObject* parent)
    : DefaultShaderLayer(
        parent,
        "FireGolfShaderLayer",
        "shader_repo/fire_golf/shaders/fire_golf.vert.spv",
        "shader_repo/fire_golf/shaders/fire_golf.frag.spv")
{

}