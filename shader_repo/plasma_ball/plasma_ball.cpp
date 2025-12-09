// copyright 2025 swaroop.

#include "plasma_ball.h"

#include "layers/plasma_ball_shader_layer.h"
#include "layers/screen_coordinates_ui_layer.h"

PlasmaBallObject::PlasmaBallObject(Engine* e) : EngineObject(e) {
    objName = "[EngineObject] Plasma Ball Shader";
}

void PlasmaBallObject::onSetup() {
    EngineObject::onSetup();

    pushLayer(new PlasmaBallShaderLayer(this));
    pushLayer(new PlasmaBallUILayer(this));
}

void PlasmaBallObject::update(float deltaTime) {
    EngineObject::update(deltaTime);
}

void PlasmaBallObject::render(VkCommandBuffer cmd) {
    EngineObject::render(cmd);
}
