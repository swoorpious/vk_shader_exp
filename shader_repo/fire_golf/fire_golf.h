// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_FIRE_GOLF_H
#define VK_SHADER_ENGINE_FIRE_GOLF_H
#include <core/engine_object.h>



class FireGolfObject final : public EngineObject {
public:
    explicit FireGolfObject(Engine* e);

    void onSetup() override;
    void update(float deltaTime) override;
    void render(VkCommandBuffer cmd) override;
};


#endif //VK_SHADER_ENGINE_FIRE_GOLF_H