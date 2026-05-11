// copyright 2025 swaroop.

#include "fire_golf.h"

#include "layers/fire_golf_shader_layer.h"
#include "layers/screen_coordinates_ui_layer.h"

FireGolfObject::FireGolfObject(Engine* e) : EngineObject(e) {
    objName = "[EngineObject] Plasma Ball Shader";
}

void FireGolfObject::onSetup() {
    EngineObject::onSetup();

    pushLayer(new FireGolfShaderLayer(this));
    pushLayer(new FireGolfUILayer(this)); // includes debug ui
}

void FireGolfObject::update(float deltaTime) {
    EngineObject::update(deltaTime);
}

void FireGolfObject::render(VkCommandBuffer cmd) {
    EngineObject::render(cmd);
}
