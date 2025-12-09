// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_SELECT_MENU_H
#define VK_SHADER_ENGINE_SELECT_MENU_H

#include <core/engine_object.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <memory>

class SelectMenuObject final : public EngineObject {
public:
    explicit SelectMenuObject(Engine* e);

    void onSetup() override;
    void update(float deltaTime) override;
    void render(VkCommandBuffer cmd) override;

    const std::vector<std::string>& getDemoNames() const;
    void launchDemo(const std::string& name);

private:
    std::unordered_map<std::string, std::function<EngineObject*(Engine*)>> repo_map;
    std::vector<std::string> demo_names;
    
    template<typename T>
    void registerClass(const std::string& name);
};

template <typename T>
void SelectMenuObject::registerClass(const std::string& name) {
    repo_map[name] = [](Engine* e) {
        return new T(e);
    };
    demo_names.push_back(name);
}

#endif //VK_SHADER_ENGINE_SELECT_MENU_H