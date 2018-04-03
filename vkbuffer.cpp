#include "vkbuffer.h"
#include "vkcore.h"

vk_buffer::vk_buffer(const VkDeviceSize &size, const VkBufferUsageFlags &usage, const VkMemoryPropertyFlags &properties) :
    mSize(size),
    mBuffer(VK_NULL_HANDLE),
    mBufferMemory(VK_NULL_HANDLE)
{
    if (mSize == 0)
    {
        return;
    }

    const auto logicalDevice = vk_core::instance().getDevice()->getDevice();

    vk_queueFamilyIndices indices = vk_core::instance().getDevice()->getQueueFamilyIndices();
    uint32_t indicesArray[] = {
        static_cast<uint32_t>(indices.graphicsFamily), static_cast<uint32_t>(indices.presentFamily)
    };

    VkBufferCreateInfo bufferCreateInfo = {};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = size;
    bufferCreateInfo.usage = usage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferCreateInfo.queueFamilyIndexCount = 2;
    bufferCreateInfo.pQueueFamilyIndices = indicesArray;

    if(vkCreateBuffer(logicalDevice, &bufferCreateInfo, nullptr, &mBuffer)){
        throw std::runtime_error("failed to create buffer!");
    }

    // Allocates buffer memory.
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(logicalDevice, mBuffer, &memoryRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo = {};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(logicalDevice, &memoryAllocateInfo, nullptr, &mBufferMemory)){
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(logicalDevice, m_buffer, m_bufferMemory, 0);
}

vk_buffer::~vk_buffer()
{
    const auto logicalDevice = vk_core::instance().getDevice()->getDevice();

    vkDestroyBuffer(logicalDevice, mBuffer, nullptr);
    vkFreeMemory(logicalDevice, mBufferMemory, nullptr);
}

uint32_t vk_buffer::findMemoryType(const uint32_t &typeFilter, const VkMemoryPropertyFlags &properties)
{
    const auto physicalDevice = vk_core::instance().getDevice()->getPhysicalDevice();

    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);

    for (uint32_t i = 0; i < physicalDeviceMemoryProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) &&
            (physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    assert(false && "Failed to find a valid memory type for buffer!");
    return 0;
}

void vk_buffer::copyBuffer(const VkBuffer srcBuffer, const VkBuffer dstBuffer, const VkDeviceSize &size)
{
    const auto logicalDevice = vk_core::instance().getDevice()->getDevice();
    const auto queue = vk_core::instance().getDevice()->getGraphicsQueue();
    const auto commandPool = vk_core::instance().getCommandPool();

    // Makes a temporary command buffer for the memory transfer operation.
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandPool = commandPool;
    commandBufferAllocateInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(logicalDevice, &commandBufferAllocateInfo, &commandBuffer);

    VkCommandBufferBeginInfo commandBufferBeginInfo = {};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);

    VkBufferCopy copyRegion = {};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(queue);

    vkFreeCommandBuffers(logicalDevice, commandPool, 1, &commandBuffer);
}
