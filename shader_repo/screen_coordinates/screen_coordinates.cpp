// copyright 2025 swaroop.

#include "screen_coordinates.h"

#include "layers/screen_coordinates_shader_layer.h"
#include "layers/screen_coordinates_ui_layer.h"

ScreenCoordinatesObject::ScreenCoordinatesObject(Engine* e) : EngineObject(e) {
    objName = "[EngineObject] Plasma Ball Shader";
}

void ScreenCoordinatesObject::onSetup() {
    EngineObject::onSetup();

    pushLayer(new ScreenCoordinatesShaderLayer(this));
    pushLayer(new ScreenCoordinatesUILayer(this));
}

void ScreenCoordinatesObject::update(float deltaTime) {
    EngineObject::update(deltaTime);
}

void ScreenCoordinatesObject::render(VkCommandBuffer cmd) {
    EngineObject::render(cmd);
}
