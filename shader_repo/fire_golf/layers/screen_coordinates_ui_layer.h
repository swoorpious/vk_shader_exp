// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_PLASMA_BALL_UI_LAYER_H
#define VK_SHADER_ENGINE_PLASMA_BALL_UI_LAYER_H
#include "templates/default_shader_debug_ui.h"


class FireGolfUILayer : public DefaultShaderDebugUILayer {
public:
    explicit FireGolfUILayer(EngineObject* parent);
    void onUpdate(float deltaTime) override;
};


#endif //VK_SHADER_ENGINE_PLASMA_BALL_UI_LAYER_H