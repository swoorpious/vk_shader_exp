// copyright 2025 swaroop.

#ifndef VK_SHADER_EXP_ENGINE_OBJECT_H
#define VK_SHADER_EXP_ENGINE_OBJECT_H

#include <vector>
#include <string>
#include "vulkan/vulkan_core.h"


class Engine;
class Viewport;
class LayerComponent;

class EngineObject {
public:
    EngineObject(Engine* engineRef);
    virtual ~EngineObject();

    virtual void onSetup() {} 

    /*
     * push layers to the render stack
     * push the debug/dev ui layer in the end so that it renders at the top of the queue 
     */
    virtual void pushLayer(LayerComponent* layer);
    virtual void popLayer(LayerComponent* layer);

    virtual void update(float deltaTime);
    virtual void render(VkCommandBuffer cmd);

    Engine* getEngine() const;
    Viewport& getViewport() const;
    std::string getName() const;

protected:
    Engine *engine = nullptr;

    // in the context of this project this is basically a shader project name
    std::string objName = "DefaultEngineObject";
    
    std::vector<LayerComponent*> layerStack; 
};


#endif // VK_SHADER_EXP_ENGINE_OBJECT_H