// copyright 2025 swaroop.

#include "screen_coordinates_ui_layer.h"
#include "engine.h"


ScreenCoordinatesUILayer::ScreenCoordinatesUILayer(EngineObject* parent)
    : DefaultShaderDebugUILayer(parent, "ScreenCoordinatesUI") 
{
}

void ScreenCoordinatesUILayer::onUpdate(float deltaTime) {
    DefaultShaderDebugUILayer::onUpdate(deltaTime);
}