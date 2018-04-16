#ifndef RENDERER_H
#define RENDERER_H

#include "../RenderAPI/vkcore.h"
#include "../RenderAPI/vkbuffer.h"
#include "../RenderAPI/vkimage.h"

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class Renderer
{
public:
    Renderer() {
    }

    ~Renderer() {}

    void init();

    void update();

    void drawFrame();

    void resize(int w,int h);

private:
    void createRenderPass();
    void createFramebuffers();
    void createDescriptorPool();
    void createDescriptorSetLayout();
    void createDescriptorSet();
    void createGraphicsPipeline();
    void createUniformBuffer();
    void createDepthImage();
    void createCommandBuffers();
    void createSemaphores();

    std::vector<VkCommandBuffer> mCommandBuffers;
    VkRenderPass mRenderPass;
    std::vector<VkFramebuffer> mSwapChainFramebuffers;

    VkDescriptorPool mDescriptorPool;
    VkDescriptorSetLayout mDescriptorSetLayout;
    VkDescriptorSet mDescriptorSet;

    VkPipelineLayout mPipelineLayout;
    VkPipeline mGraphicsPipeline;

    VkSemaphore mImageAvailableSemaphore;
    VkSemaphore mRenderFinishedSemaphore;

    std::shared_ptr<vk_buffer> mUniformBuffer;
    std::shared_ptr<vk_image> mDepthImage;
};

#endif
