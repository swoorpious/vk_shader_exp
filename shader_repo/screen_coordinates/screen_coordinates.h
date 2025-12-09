// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_SCREEN_COORDINATES_H
#define VK_SHADER_ENGINE_SCREEN_COORDINATES_H
#include <core/engine_object.h>


class ScreenCoordinatesObject final : public EngineObject {
public:
    explicit ScreenCoordinatesObject(Engine* e);

    void onSetup() override;
    void update(float deltaTime) override;
    void render(VkCommandBuffer cmd) override;
};


#endif //VK_SHADER_ENGINE_SCREEN_COORDINATES_H