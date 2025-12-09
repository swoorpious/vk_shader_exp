// copyright 2025 swaroop.

#include <select_menu/select_menu_layer.h>
#include <select_menu/select_menu.h>
#include <imgui/imgui.h>
#include <engine.h>
#include <util/viewport.h>
#include <SDL3/SDL.h>

// #include "sdl/include/SDL3/SDL_events.h"

SelectMenuLayer::SelectMenuLayer(EngineObject* parent) 
    : LayerComponent(parent, "SelectMenuLayer") 
{
}

void SelectMenuLayer::onAttach() {
}

/*
 * @brief AI-Generated sloppy menu
 */
void SelectMenuLayer::onUpdate(float deltaTime) {
    Engine* engine = getEngine(); 
    if (!engine) return;

    auto* menuObject = dynamic_cast<SelectMenuObject*>(getParent());
    if (!menuObject) return;

    auto& viewport = engine->getViewport();
    auto window_size = viewport.getLogicalSize();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    if (ImGui::Begin("Main Menu", nullptr, 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoBringToFrontOnFocus)) 
    {
        ImGui::SetCursorPosY(window_size.y * 0.2f);
        
        auto centerText = [&](const char* text, float scale = 1.0f) {
            ImGui::SetWindowFontScale(scale);
            float textWidth = ImGui::CalcTextSize(text).x;
            ImGui::SetCursorPosX((window_size.x - textWidth) * 0.5f);
            ImGui::Text("%s", text);
            ImGui::SetWindowFontScale(1.0f);
        };

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 1.0f, 1.0f)); // Cyan
        centerText("VK SHADER ENGINE", 2.0f);
        ImGui::PopStyleColor();
        
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        const auto& demos = menuObject->getDemoNames();
        int totalItems = static_cast<int>(demos.size()) + 1; // Demos + Quit button
        static int selectedIndex = 0;

        if (ImGui::IsKeyPressed(ImGuiKey_UpArrow) || ImGui::IsKeyPressed(ImGuiKey_W)) {
            selectedIndex = (selectedIndex - 1 + totalItems) % totalItems;
        }
        if (ImGui::IsKeyPressed(ImGuiKey_DownArrow) || ImGui::IsKeyPressed(ImGuiKey_S)) {
            selectedIndex = (selectedIndex + 1) % totalItems;
        }
        bool triggerEnter = ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_Space) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter);

        float buttonWidth = 200.0f;
        float buttonHeight = 40.0f;
        int currentIndex = 0;

        for (const auto& name : demos) {
            ImGui::SetCursorPosX((window_size.x - buttonWidth) * 0.5f);
            
            bool isSelected = (currentIndex == selectedIndex);
            if (isSelected) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.6f, 0.6f, 1.0f));
            }

            if (ImGui::Button(name.c_str(), ImVec2(buttonWidth, buttonHeight)) || (isSelected && triggerEnter)) {
                if (isSelected) ImGui::PopStyleColor();
                else { /* nothing to pop */ }

                ImGui::End();
                ImGui::PopStyleVar();
                ImGui::PopStyleColor();

                menuObject->launchDemo(name);
                return;
            }

            if (isSelected) ImGui::PopStyleColor();
            
            if (ImGui::IsItemHovered()) selectedIndex = currentIndex;

            ImGui::Spacing();
            currentIndex++;
        }

        ImGui::Spacing();
        ImGui::SetCursorPosX((window_size.x - buttonWidth) * 0.5f);
        
        bool isQuitSelected = (currentIndex == selectedIndex);
        ImVec4 quitColor = isQuitSelected ? ImVec4(0.9f, 0.2f, 0.2f, 1.0f) : ImVec4(0.5f, 0.1f, 0.1f, 1.0f);
        
        ImGui::PushStyleColor(ImGuiCol_Button, quitColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        
        if (ImGui::Button("Quit", ImVec2(buttonWidth, buttonHeight)) || (isQuitSelected && triggerEnter)) {
            SDL_Event quit_event{}; 
            quit_event.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&quit_event);
        }
        
        if (ImGui::IsItemHovered()) selectedIndex = currentIndex;

        ImGui::PopStyleColor(2);
    }
    ImGui::End();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}