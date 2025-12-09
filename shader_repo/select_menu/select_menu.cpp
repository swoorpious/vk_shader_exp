// copyright 2025 swaroop.

#include "select_menu.h"
#include "select_menu_layer.h"
#include <engine.h>

// Include your shader headers here
#include <plasma_ball/plasma_ball.h>
#include <screen_coordinates/screen_coordinates.h>

SelectMenuObject::SelectMenuObject(Engine* e): EngineObject(e) {
    objName = "[EngineObject] Select Menu";
}

void SelectMenuObject::onSetup() {
    EngineObject::onSetup();
    
    registerClass<PlasmaBallObject>("Plasma Ball");
    registerClass<ScreenCoordinatesObject>("Screen Coordinates");
    
    pushLayer(new SelectMenuLayer(this));
}

void SelectMenuObject::update(float deltaTime) {
    EngineObject::update(deltaTime);
}

void SelectMenuObject::render(VkCommandBuffer cmd) {
    EngineObject::render(cmd);
}

const std::vector<std::string>& SelectMenuObject::getDemoNames() const {
    return demo_names;
}

void SelectMenuObject::launchDemo(const std::string& name) {
    auto it = repo_map.find(name);
    if (it != repo_map.end()) {
        EngineObject* newApp = it->second(engine);
        engine->switchProject(newApp);
    }
}