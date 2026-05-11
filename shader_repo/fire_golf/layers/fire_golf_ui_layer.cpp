// copyright 2025 swaroop.

#include "screen_coordinates_ui_layer.h"
#include "engine.h"


FireGolfUILayer::FireGolfUILayer(EngineObject* parent)
    : DefaultShaderDebugUILayer(parent, "PlasmaBallUI") 
{
}

void FireGolfUILayer::onUpdate(float deltaTime) {
    DefaultShaderDebugUILayer::onUpdate(deltaTime);
}