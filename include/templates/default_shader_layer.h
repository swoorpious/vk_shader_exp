// copyright 2025 swaroop.

#ifndef VK_SHADER_ENGINE_DEFAULT_SHADER_LAYER_H
#define VK_SHADER_ENGINE_DEFAULT_SHADER_LAYER_H

#include <core/layer_component.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>

class DefaultShaderLayer : public LayerComponent {
public:
    DefaultShaderLayer(EngineObject* parent, const std::string& name, std::string vertPath, std::string fragPath);
    ~DefaultShaderLayer() override = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(float deltaTime) override;
    void onRender(VkCommandBuffer cmd) override;

protected:
    VkDevice device = VK_NULL_HANDLE;
    float totalTime = 0.0f;

private:
    void createResources();
    void createPipeline();
    void updateUniforms();

    std::string vertexShaderPath;
    std::string fragmentShaderPath;

    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
    
    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;

    VkBuffer uniformBuffer = VK_NULL_HANDLE;
    VkDeviceMemory uniformBufferMemory = VK_NULL_HANDLE;
    void* mappedData = nullptr;


    struct UniformBufferObject {
        float resolution[2];
        float time;
        float padding;
    };
};

#endif // VK_SHADER_ENGINE_DEFAULT_SHADER_LAYER_H