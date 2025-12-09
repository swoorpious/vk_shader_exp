// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_DEFAULT_SHADER_DEBUG_UI_H
#define VK_SHADER_ENGINE_DEFAULT_SHADER_DEBUG_UI_H
#include "core/layer_component.h"


class DefaultShaderDebugUILayer : public LayerComponent {
public:
    explicit DefaultShaderDebugUILayer(EngineObject* parent, const std::string& name = "DebugLayer");
    void onUpdate(float deltaTime) override;

private:
    std::string debug_layer_name = "DebugLayer";
};


#endif //VK_SHADER_ENGINE_DEFAULT_SHADER_DEBUG_UI_H