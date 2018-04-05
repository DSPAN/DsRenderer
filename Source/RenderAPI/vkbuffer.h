#ifndef VK_BUFFER_H
#define VK_BUFFER_H
#include "util.h"

class  vk_buffer
{
public:
    vk_buffer(const VkDeviceSize &size, const VkBufferUsageFlags &usage, const VkMemoryPropertyFlags &properties);

    ~vk_buffer();

    VkDeviceSize getSize() const { return mSize; }

    VkBuffer getBuffer() const { return mBuffer; }

    VkDeviceMemory getBufferMemory() const { return mBufferMemory; }

    static uint32_t findMemoryType(const uint32_t &typeFilter, const VkMemoryPropertyFlags &properties);

    static void copyBuffer(const VkBuffer srcBuffer, const VkBuffer dstBuffer, const VkDeviceSize &size);
protected:
    VkDeviceSize mSize;
    VkBuffer mBuffer;
    VkDeviceMemory mBufferMemory;
};

#endif // VKBUFFER_H
