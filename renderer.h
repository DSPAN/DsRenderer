#ifndef RENDERER_H
#define RENDERER_H
#include "util.h"
#include "vkswapchain.h"

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};
class Renderer
{
public:
    Renderer(std::shared_ptr<vk_device> device) {
        mDevice = device;
    }
    drawFrame();
private:
    void createCommandPool();
    VkCommandBuffer createCommand();
    void createRenderPass();
    void createFramebuffers();
    void createDescriptorPool();
    void createDescriptorSetLayout();
    void createDescriptorSet();
    void createGraphicsPipeline();
    void createUniformBuffer();

    std::vector<VkCommandBuffer> mCommandBuffers;
    VkRenderPass mRenderPass;
    std::vector<VkFramebuffer> mSwapChainFramebuffers;

    VkDescriptorPool mDescriptorPool;
    VkDescriptorSetLayout mDescriptorSetLayout;
    VkDescriptorSet mDescriptorSet;

    VkPipelineLayout mPipelineLayout;
    VkPipeline mGraphicsPipeline;

    VkBuffer mUniformBuffer;
    VkDeviceMemory mUniformBufferMemory;

    std::shared_ptr<vk_device> mDevice;
};

#endif
