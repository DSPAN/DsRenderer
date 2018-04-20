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
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(mDevice->getDevice(), &poolInfo, nullptr, &mCommandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

VkCommandBuffer vk_core::beginSingleTimeCommands(const VkCommandBufferLevel &level) {
    const auto logicalDevice = mDevice->getDevice();

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = level;
    allocInfo.commandPool = mCommandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    if(vkAllocateCommandBuffers(logicalDevice, &allocInfo, &commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffer!");
    }

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS){
        throw std::runtime_error("failed to begin command buffer!");
    }

    return commandBuffer;
}

void vk_core::endSingleTimeCommands(const VkCommandBuffer &commandBuffer)
{
    const auto logicalDevice = mDevice->getDevice();
    const auto queue = mDevice->getGraphicsQueue();

    if(vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to end command buffer!");
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    if(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
        throw std::runtime_error("failed to queue submit!");
    }

    if(vkQueueWaitIdle(queue) != VK_SUCCESS) {
        throw std::runtime_error("failed to queue wait idle!");
    }

    vkFreeCommandBuffers(logicalDevice, mCommandPool, 1, &commandBuffer);
}

