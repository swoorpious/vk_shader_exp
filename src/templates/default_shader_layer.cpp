// copyright 2025 swaroop.

#include <templates/default_shader_layer.h>
#include <engine.h>
#include <util/viewport.h>
#include <core/engine_object.h>

#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <algorithm>

#define VK_CHECK(x) do { if ((x) != VK_SUCCESS) throw std::runtime_error("Vulkan Error in DefaultShaderLayer"); } while (0)

/*
 * @brief AI-Generated sloppy helper function
 */
static std::vector<char> readFile(const std::string& filename) {
    auto tryPath = [&](std::string p) {
        std::ifstream f(p, std::ios::ate | std::ios::binary);
        if (!f.is_open()) return std::vector<char>{};
        size_t size = (size_t)f.tellg();
        std::vector<char> buf(size);
        f.seekg(0); f.read(buf.data(), size);
        return buf;
    };

    // multiple search directories to locate the shader files
    auto data = tryPath(filename);
    if (data.empty()) data = tryPath("../" + filename);
    if (data.empty()) data = tryPath("../../" + filename);
    if (data.empty()) data = tryPath("../../../" + filename);
    
    if (data.empty() && filename.find("shader_repo/") == std::string::npos) {
         data = tryPath("../../shader_repo/" + filename); 
    }

    if (data.empty()) {
        std::cerr << "[Shader Error] Could not find file: " << filename << "\nCWD: " << std::filesystem::current_path() << "\n";
        throw std::runtime_error("Shader missing: " + filename);
    }
    return data;
}


DefaultShaderLayer::DefaultShaderLayer(EngineObject* parent, const std::string& name, std::string vertPath, std::string fragPath)
    : LayerComponent(parent, name)
    , vertexShaderPath(std::move(vertPath))
    , fragmentShaderPath(std::move(fragPath))
{
    if (auto* e = getEngine()) device = e->getDevice();
}

void DefaultShaderLayer::onAttach() {
    createResources();
    createPipeline();
}

void DefaultShaderLayer::onDetach() {
    if (!device) return;
    vkDeviceWaitIdle(device);

    auto safeDestroy = [&](auto& obj, auto deleter) { 
        if (obj) { deleter(device, obj, nullptr); obj = VK_NULL_HANDLE; } 
    };

    safeDestroy(graphicsPipeline, vkDestroyPipeline);
    safeDestroy(pipelineLayout, vkDestroyPipelineLayout);
    safeDestroy(descriptorPool, vkDestroyDescriptorPool);
    safeDestroy(descriptorSetLayout, vkDestroyDescriptorSetLayout);
    safeDestroy(uniformBuffer, vkDestroyBuffer);
    
    if (uniformBufferMemory) { vkFreeMemory(device, uniformBufferMemory, nullptr); uniformBufferMemory = VK_NULL_HANDLE; }
    mappedData = nullptr;
}

void DefaultShaderLayer::onUpdate(float deltaTime) {
    totalTime += deltaTime;
    updateUniforms();
}

void DefaultShaderLayer::onRender(VkCommandBuffer cmd) {
    if (!graphicsPipeline) return;

    auto size = getEngine()->getViewport().getLogicalSize();
    if (size.x <= 0 || size.y <= 0) return;

    VkViewport vp{ 0.0f, 0.0f, size.x, size.y, 0.0f, 1.0f };
    VkRect2D sci{ {0, 0}, {(uint32_t)size.x, (uint32_t)size.y} };

    vkCmdSetViewport(cmd, 0, 1, &vp);
    vkCmdSetScissor(cmd, 0, 1, &sci);
    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    vkCmdBindDescriptorSets(
        cmd, 
        VK_PIPELINE_BIND_POINT_GRAPHICS, 
        pipelineLayout, 
        0, 
        1, 
        &descriptorSet, 
        0, 
        nullptr);
    vkCmdDraw(cmd, 3, 1, 0, 0);
}

void DefaultShaderLayer::createResources() {
    VkPhysicalDevice gpu = getEngine()->getPhysicalDevice();

    // memory type finder
    auto findMem = [&](uint32_t filter, VkMemoryPropertyFlags props) {
        VkPhysicalDeviceMemoryProperties mem;
        vkGetPhysicalDeviceMemoryProperties(gpu, &mem);
        for (uint32_t i = 0; i < mem.memoryTypeCount; i++)
            if ((filter & (1 << i)) && (mem.memoryTypes[i].propertyFlags & props) == props) return i;
        throw std::runtime_error("No suitable memory");
    };

    // uniform buffer
    VkDeviceSize size = sizeof(UniformBufferObject);
    VkBufferCreateInfo bufInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, 
        nullptr, 
        0, 
        size, 
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
        VK_SHARING_MODE_EXCLUSIVE };
    VK_CHECK(vkCreateBuffer(device, &bufInfo, nullptr, &uniformBuffer));

    VkMemoryRequirements memReq;
    vkGetBufferMemoryRequirements(device, uniformBuffer, &memReq);
    VkMemoryAllocateInfo allocInfo{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, 
        nullptr, 
        memReq.size, 
        findMem(memReq.memoryTypeBits, 
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) };
    
    VK_CHECK(vkAllocateMemory(device, 
        &allocInfo, 
        nullptr, 
        &uniformBufferMemory));
    VK_CHECK(vkBindBufferMemory(device, 
        uniformBuffer, 
        uniformBufferMemory, 
        0));
    VK_CHECK(vkMapMemory(device, 
        uniformBufferMemory, 
        0, 
        size, 
        0, 
        &mappedData));

    /*
     * descriptors
     * not formatted because i coped these
     */
    VkDescriptorPoolSize poolSize{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1 };
    VkDescriptorPoolCreateInfo poolInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, nullptr, 0, 1, 1, &poolSize };
    VK_CHECK(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool));

    VkDescriptorSetLayoutBinding binding{ 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr };
    VkDescriptorSetLayoutCreateInfo layInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, nullptr, 0, 1, &binding };
    VK_CHECK(vkCreateDescriptorSetLayout(device, &layInfo, nullptr, &descriptorSetLayout));

    VkDescriptorSetAllocateInfo allocSetInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, nullptr, descriptorPool, 1, &descriptorSetLayout };
    VK_CHECK(vkAllocateDescriptorSets(device, &allocSetInfo, &descriptorSet));

    VkDescriptorBufferInfo dbi{ uniformBuffer, 0, size };
    VkWriteDescriptorSet write{ VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, descriptorSet, 0, 0, 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, nullptr, &dbi, nullptr };
    vkUpdateDescriptorSets(device, 1, &write, 0, nullptr);
}

void DefaultShaderLayer::createPipeline() {
    auto createMod = [&](const std::string& path) {
        auto code = readFile(path);
        VkShaderModuleCreateInfo info{ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, nullptr, 0, code.size(), (uint32_t*)code.data() };
        VkShaderModule mod;
        VK_CHECK(vkCreateShaderModule(device, &info, nullptr, &mod));
        return mod;
    };

    VkShaderModule vs = createMod(vertexShaderPath);
    VkShaderModule fs = createMod(fragmentShaderPath);

    VkPipelineShaderStageCreateInfo stages[] = {
        { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            nullptr,
            0,
            VK_SHADER_STAGE_VERTEX_BIT,
            vs,
            "main" },
        { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            nullptr,
            0,
            VK_SHADER_STAGE_FRAGMENT_BIT,
            fs,
            "main" }
    };

    /*
     * code to generate the standard screen triangle
     */
    VkPipelineVertexInputStateCreateInfo vi{
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
    VkPipelineInputAssemblyStateCreateInfo ia{
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        VK_FALSE
    };
    VkPipelineViewportStateCreateInfo vp{
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        nullptr,
        0,
        1,
        nullptr,
        1,
        nullptr
    };
    VkPipelineRasterizationStateCreateInfo rs{
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_FALSE,
        VK_FALSE,
        VK_POLYGON_MODE_FILL,
        VK_CULL_MODE_NONE,
        VK_FRONT_FACE_COUNTER_CLOCKWISE,
        VK_FALSE,
        0,
        0,
        0,
        1.0f
    };
    VkPipelineMultisampleStateCreateInfo ms{
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_SAMPLE_COUNT_1_BIT,
        VK_FALSE,
        1.0f,
        nullptr,
        VK_FALSE,
        VK_FALSE
    };
    

    // some more bullshit
    VkPipelineColorBlendAttachmentState att{};
    att.blendEnable = VK_FALSE;
    att.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    att.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    att.colorBlendOp = VK_BLEND_OP_ADD;
    att.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    att.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    att.alphaBlendOp = VK_BLEND_OP_ADD;
    att.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo cb{ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_FALSE,
        VK_LOGIC_OP_COPY,
        1,
        &att,
        {0,0,0,0}
    };
    
    VkPipelineLayoutCreateInfo pli{
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        nullptr,
        0,
        1,
        &descriptorSetLayout,
        0,
        nullptr
    };
    VK_CHECK(vkCreatePipelineLayout(device, &pli, nullptr, &pipelineLayout));

    VkDynamicState dynStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dyn{
        VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        nullptr,
        0,
        2,
        dynStates
    };

    VkGraphicsPipelineCreateInfo pci{ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
    pci.stageCount = 2; pci.pStages = stages;
    pci.pVertexInputState = &vi; pci.pInputAssemblyState = &ia;
    pci.pViewportState = &vp; pci.pRasterizationState = &rs;
    pci.pMultisampleState = &ms; pci.pColorBlendState = &cb;
    pci.pDynamicState = &dyn; pci.layout = pipelineLayout;
    pci.renderPass = getEngine()->getRenderPass();
    pci.subpass = 0;
    pci.pDepthStencilState = nullptr; // disable depth

    VK_CHECK(vkCreateGraphicsPipelines(
        device,
        VK_NULL_HANDLE,
        1,
        &pci,
        nullptr,
        &graphicsPipeline
    ));

    vkDestroyShaderModule(device, vs, nullptr);
    vkDestroyShaderModule(device, fs, nullptr);
}

void DefaultShaderLayer::updateUniforms() {
    if (!mappedData) return;
    auto size = getEngine()->getViewport().getLogicalSize();
    UniformBufferObject ubo{ {std::max(1.0f, size.x), std::max(1.0f, size.y)}, totalTime, 0.0f };
    memcpy(mappedData, &ubo, sizeof(ubo));
}