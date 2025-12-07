// copyright 2025 swaroop.

#include "select_menu.h"
// #include <plasma_ball/plasma.h>
#include <imgui/imgui.h>
#include <engine.h>


SelectMenuObject::SelectMenuObject(Engine* e): EngineObject(e) {
}

void SelectMenuObject::onSetup() {
    EngineObject::onSetup();
    // this->registerClass<PlasmaBallObject>("Plasma Ball by Xor Dev");
    time_elapsed = 0.0f;
}

void SelectMenuObject::update(float deltaTime) {
    EngineObject::update(deltaTime);
    time_elapsed += deltaTime;

    auto& viewport = engine->getViewport();
    auto window_size = viewport.getLogicalSize();

    ImVec2 center(window_size.x * 0.5f, window_size.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
        
        ImGui::Text("select_menu");
        ImGui::Text("time since loaded: %.2fs", time_elapsed);

    }
    ImGui::End();
}

void SelectMenuObject::render() {
    EngineObject::render();
}

