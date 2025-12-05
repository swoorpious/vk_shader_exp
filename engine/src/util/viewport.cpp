// copyright 2025 swaroop.

#include <util/viewport.h>
#include "vulkan/vulkan_core.h"

Viewport::Viewport(VkViewport vk_viewport) {}


windowStates Viewport::getWindowState() {
    return viewportState.winState;
}

void Viewport::setWindowState(windowStates state) {}

Math::Vector2f Viewport::getWinSize() {}

void Viewport::setWinSize(Math::Vector2f dimensions) {}

Math::Vector2f Viewport::getWinLocation() {}

void Viewport::setWinLocation(Math::Vector2f location) {}

Math::Vector2f Viewport::getViewSize() {}

void Viewport::setViewSize(Math::Vector2f size) {}

Math::Vector2f Viewport::getWinSizeMinMax() {}

void Viewport::setWinSizeMinMax(Math::Vector2f minMax) {}

Math::Vector2f Viewport::getWinDepth() {}

void Viewport::setWinDepth(Math::Vector2f depth) {}

float Viewport::getViewScale() {}

void Viewport::setViewScale(float scale) {}
