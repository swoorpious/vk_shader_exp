// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_PLASMA_BALL_SHADER_LAYER_H
#define VK_SHADER_ENGINE_PLASMA_BALL_SHADER_LAYER_H

#include <templates/default_shader_layer.h>

class PlasmaBallShaderLayer final : public DefaultShaderLayer {
public:
    explicit PlasmaBallShaderLayer(EngineObject* parent);
    ~PlasmaBallShaderLayer() override = default;
};

#endif // VK_SHADER_ENGINE_PLASMA_BALL_SHADER_LAYER_H