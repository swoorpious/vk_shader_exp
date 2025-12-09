// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_SCREEN_COORDINATES_SHADER_LAYER_H
#define VK_SHADER_ENGINE_SCREEN_COORDINATES_SHADER_LAYER_H

#include <templates/default_shader_layer.h>

class ScreenCoordinatesShaderLayer final : public DefaultShaderLayer {
public:
    explicit ScreenCoordinatesShaderLayer(EngineObject* parent);
    ~ScreenCoordinatesShaderLayer() override = default;
};

#endif // VK_SHADER_ENGINE_SCREEN_COORDINATES_SHADER_LAYER_H