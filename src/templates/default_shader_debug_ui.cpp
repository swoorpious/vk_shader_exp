// copyright 2025 swaroop.

#include <templates/default_shader_debug_ui.h>
#include <imgui/imgui.h>

#include "engine.h"
#include "select_menu/select_menu.h"

DefaultShaderDebugUILayer::DefaultShaderDebugUILayer(EngineObject* parent, const std::string& name)
    : LayerComponent(parent, name) 
{
    debug_layer_name = name;
}

void DefaultShaderDebugUILayer::onUpdate(float deltaTime) {
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowBgAlpha(0.0f);
    if (ImGui::Begin(debug_layer_name.c_str(), nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav
        )) {
        
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 1.0f, 1.0f)); 
        
        if (ImGui::Button("< back [esc]") || ImGui::IsKeyPressed(ImGuiKey_Escape)) {
            getEngine()->switchProject(new SelectMenuObject(getEngine()));
        }
        
        ImGui::PopStyleColor();
    }
    ImGui::End();
}