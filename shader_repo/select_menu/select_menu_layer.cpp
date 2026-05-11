// copyright 2025 swaroop.

#include <select_menu/select_menu_layer.h>
#include <select_menu/select_menu.h>
#include <imgui/imgui.h>
#include <engine.h>
#include <util/viewport.h>
#include <SDL3/SDL.h>
#include <string>

SelectMenuLayer::SelectMenuLayer(EngineObject* parent) 
    : LayerComponent(parent, "SelectMenuLayer") 
{
}

void SelectMenuLayer::onAttach() {
}

void SelectMenuLayer::onUpdate(float deltaTime) {
    Engine* engine = getEngine(); 
    if (!engine) return;

    auto* menuObject = dynamic_cast<SelectMenuObject*>(getParent());
    if (!menuObject) return;

    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowBgAlpha(0.0f);
    
    if (ImGui::Begin("Main Menu", nullptr, 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav)) 
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 1.0f, 1.0f)); 
        
        ImGui::Text("vulkan shader engine");
        ImGui::Separator();
        ImGui::Spacing();

        const auto& demos = menuObject->getDemoNames();
        int totalItems = static_cast<int>(demos.size()) + 1;
        static int selectedIndex = 0;

        // Arrow key navigation
        if (ImGui::IsKeyPressed(ImGuiKey_UpArrow) || ImGui::IsKeyPressed(ImGuiKey_W)) {
            selectedIndex = (selectedIndex - 1 + totalItems) % totalItems;
        }
        if (ImGui::IsKeyPressed(ImGuiKey_DownArrow) || ImGui::IsKeyPressed(ImGuiKey_S)) {
            selectedIndex = (selectedIndex + 1) % totalItems;
        }
        bool triggerEnter = ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_Space) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter);

        int currentIndex = 0;

        for (const auto& name : demos) {
            std::string buttonText = "[" + std::to_string(currentIndex + 1) + "] " + name;
            
            ImGuiKey numKey = static_cast<ImGuiKey>(ImGuiKey_1 + currentIndex);
            bool shortcutPressed = (currentIndex <= 8) && ImGui::IsKeyPressed(numKey);
            
            bool isSelected = (currentIndex == selectedIndex);
            if (isSelected) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.4f, 0.4f, 1.0f)); // cyan highlight
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));
            }
            
            if (ImGui::Button(buttonText.c_str()) || shortcutPressed || (isSelected && triggerEnter)) {
                if (isSelected) ImGui::PopStyleColor(2);
                ImGui::PopStyleColor();
                ImGui::End();
                
                menuObject->launchDemo(name);
                return;
            }

            if (isSelected) ImGui::PopStyleColor(2);
            if (ImGui::IsItemHovered()) selectedIndex = currentIndex;

            currentIndex++;
        }

        ImGui::Spacing();
        
        // quit button
        bool isQuitSelected = (currentIndex == selectedIndex);
        
        if (isQuitSelected) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.15f, 0.15f, 1.0f));
        }

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
        if (ImGui::Button("Quit [esc]") || ImGui::IsKeyPressed(ImGuiKey_Escape) || (isQuitSelected && triggerEnter)) {
            SDL_Event quit_event{}; 
            quit_event.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&quit_event);
        }
        
        if (isQuitSelected) ImGui::PopStyleColor(2);
        if (ImGui::IsItemHovered()) selectedIndex = currentIndex;

        ImGui::PopStyleColor(2);
    }
    ImGui::End();
}