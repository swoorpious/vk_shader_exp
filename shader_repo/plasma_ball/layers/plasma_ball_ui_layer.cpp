// copyright 2025 swaroop.

#include "screen_coordinates_ui_layer.h"
#include "engine.h"


PlasmaBallUILayer::PlasmaBallUILayer(EngineObject* parent)
    : DefaultShaderDebugUILayer(parent, "PlasmaBallUI") 
{
}

void PlasmaBallUILayer::onUpdate(float deltaTime) {
    DefaultShaderDebugUILayer::onUpdate(deltaTime);
}