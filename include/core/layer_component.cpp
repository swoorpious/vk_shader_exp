// copyright 2025 swaroop.

#include <core/layer_component.h>

LayerComponent::LayerComponent(EngineObject* initializerObj, const std::string& name) {
    if (initializerObj)
        parent = initializerObj;

    if (!name.empty())
        debugName = name;
}
void LayerComponent::setEngine(Engine* engineRef) { engine = engineRef; }
const std::string& LayerComponent::getName() const { return debugName; }