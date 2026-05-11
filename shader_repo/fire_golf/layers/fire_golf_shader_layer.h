// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_PLASMA_BALL_SHADER_LAYER_H
#define VK_SHADER_ENGINE_PLASMA_BALL_SHADER_LAYER_H

#include <templates/default_shader_layer.h>

class FireGolfShaderLayer final : public DefaultShaderLayer {
public:
    explicit FireGolfShaderLayer(EngineObject* parent);
    ~FireGolfShaderLayer() override = default;
};

#endif // VK_SHADER_ENGINE_PLASMA_BALL_SHADER_LAYER_H