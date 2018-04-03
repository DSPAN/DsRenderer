#include "vkcore.h"

VkCommandBuffer vk_core::createCommand() {
    VkCommandBuffer cmdBuffer;

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = mCommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(mDevice->getDevice(), &allocInfo, &cmdBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    return cmdBuffer;
}

void vk_core::createCommandPool() {
    uint32_t queueFamilyIndex;
    const auto &queueFamilyIndices = mDevice->getQueueFamilyIndices();

    queueFamilyIndex = queueFamilyIndices.graphicsFamily;
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndex;

    if (vkCreateCommandPool(mDevice->getDevice(), &poolInfo, nullptr, &mCommandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

