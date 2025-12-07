// copyright 2025 swaroop.

#ifndef VK_SHADER_EXP_ENGINE_OBJECT_H
#define VK_SHADER_EXP_ENGINE_OBJECT_H

#include <vector>
#include <string>

class Engine;
class Viewport;
class LayerComponent;

class EngineObject {
public:
    EngineObject(Engine* engineRef);
    virtual ~EngineObject();

    virtual void onSetup() {} 

    virtual void pushLayer(LayerComponent* layer);
    virtual void popLayer(LayerComponent* layer);

    virtual void update(float deltaTime);
    virtual void render();

    Engine* getEngine() const;
    Viewport& getViewport() const;
    std::string getName() const;

protected:
    Engine *engine = nullptr;
    std::string objName = "DefaultEngineObject";
    
    std::vector<LayerComponent*> layerStack; 
};


#endif // VK_SHADER_EXP_ENGINE_OBJECT_H