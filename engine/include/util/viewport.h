// copyright 2025 swaroop.

#ifndef VK_SHADER_EXP_VIEWPORT_H
#define VK_SHADER_EXP_VIEWPORT_H


#include "math.h"

struct VkViewport;

enum windowStates {
    Windowed,
    Fullscreen,
    WindowedFullscreen
};

struct viewportData {
    Math::Vector2f winLocation = Math::Vector2f();
    Math::Vector2f winSize = Math::Vector2f(); // x: width, y: height
    Math::Vector2f winSizeMinMax = Math::Vector2f(); // x: min, y: max
    Math::Vector2f winDepth = Math::Vector2f(); // x: min, y: max
    windowStates winState = Windowed;

    Math::Vector2f viewSize = Math::Vector2f(); // resolution -> x: width, y: height
    float viewScale = 1.0;
};

class Viewport {
public:
    explicit Viewport(VkViewport vk_viewport);
    virtual ~Viewport() = 0;

    windowStates getWindowState();
    void setWindowState(windowStates state);
    Math::Vector2f getWinSize();
    void setWinSize(Math::Vector2f dimensions);
    Math::Vector2f getWinLocation();
    void setWinLocation(Math::Vector2f location);
    Math::Vector2f getViewSize();
    void setViewSize(Math::Vector2f size);
    Math::Vector2f getWinSizeMinMax();
    void setWinSizeMinMax(Math::Vector2f minMax);
    Math::Vector2f getWinDepth();
    void setWinDepth(Math::Vector2f depth);
    float getViewScale();
    void setViewScale(float scale);
    
    
    
private:
    viewportData viewportState;
};

#endif //VK_SHADER_EXP_VIEWPORT_H