// copyright 2025 swaroop.

#ifndef VK_SHADER_EXP_ENGINE_H
#define VK_SHADER_EXP_ENGINE_H

#include <util/viewport.h>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

struct SDL_Window;

// Forward Declaration
class EngineObject;

class Engine {
public:
    Engine();
    ~Engine();

    void run();
    void switchProject(EngineObject* new_app);

    Viewport& getViewport() { return viewport; }
    SDL_Window* getWindow() { return window; }

private:
    SDL_Window* window = nullptr;
    Viewport viewport;
    EngineObject* current_app = nullptr;

    VkInstance instance{};
    VkSurfaceKHR surface{};
    VkPhysicalDevice physicalDevice{};
    VkDevice device{};
    VkQueue graphicsQueue{};
    uint32_t graphicsQueueFamily{};
    VkCommandPool commandPool{};
    std::vector<VkCommandBuffer> commandBuffers;

    VkSwapchainKHR swapchain{};
    VkExtent2D swapchainExtent{};
    std::vector<VkFramebuffer> framebuffers;
    size_t currentFrame = 0;

    VkDescriptorPool imguiPool{};
    VkRenderPass imguiRenderPass{};

    void initSDL();
    void initWindow();
    void initVulkan();
    void initImGui();
    void createImGuiPool();
    void createImGuiRenderPass();


    // swapchain & buffer helpers
    void createSwapchain();
    void createFramebuffers();
    void createCommandBuffers();
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer cmd);

    friend class EngineObject;
};

#endif // VK_SHADER_EXP_ENGINE_H
