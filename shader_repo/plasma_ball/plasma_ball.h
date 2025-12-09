// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_PLASMA_BALL_H
#define VK_SHADER_ENGINE_PLASMA_BALL_H
#include <core/engine_object.h>



class PlasmaBallObject final : public EngineObject {
public:
    explicit PlasmaBallObject(Engine* e);

    void onSetup() override;
    void update(float deltaTime) override;
    void render(VkCommandBuffer cmd) override;
};


#endif //VK_SHADER_ENGINE_PLASMA_BALL_H