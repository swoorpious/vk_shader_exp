// copyright 2025 swaroop.

#include <core/engine_object.h>
#include <core/layer_component.h>
#include <engine.h>
#include <algorithm>
#include <cstdio>


EngineObject::EngineObject(Engine* engineRef) : engine(engineRef) {
}

EngineObject::~EngineObject() {
    for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
        (*it)->onDetach();
        delete (*it);
    }
    layerStack.clear();
}

void EngineObject::pushLayer(LayerComponent* layer) {
    layer->setEngine(engine);
    
    layerStack.push_back(layer);
    layer->onAttach();
    
    printf("[%s] pushed render layer: %s\n", objName.c_str(), layer->getName().c_str());
}

void EngineObject::popLayer(LayerComponent* layer) {
    auto it = std::find(layerStack.begin(), layerStack.end(), layer);
    if (it != layerStack.end()) {
        layer->onDetach();
        layerStack.erase(it);
        printf("[%s] render popped layer: %s\n", objName.c_str(), layer->getName().c_str());
    }
}

void EngineObject::update(float deltaTime) {
    for (LayerComponent* layer : layerStack) {
        layer->onUpdate(deltaTime);
    }
}

void EngineObject::render(VkCommandBuffer cmd) {
    for (LayerComponent* layer : layerStack) {
        layer->onRender(cmd);
    }
}

Engine* EngineObject::getEngine() const {
    return engine;
}

Viewport& EngineObject::getViewport() const {
    return engine->viewport; 
}

std::string EngineObject::getName() const {
    return objName;
}
