// copyright 2025 swaroop.

#include "plasma_ball_shader_layer.h"

PlasmaBallShaderLayer::PlasmaBallShaderLayer(EngineObject* parent)
    : DefaultShaderLayer(
        parent,
        "PlasmaBallShaderLayer",
        "shader_repo/plasma_ball/shaders/plasma_ball.vert.spv",
        "shader_repo/plasma_ball/shaders/plasma_ball.frag.spv")
{

}