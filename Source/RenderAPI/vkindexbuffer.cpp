#include "vkindexbuffer.h"
#include "vkcore.h"

vk_indexBuffer::vk_indexBuffer(const VkIndexType &indexType, const uint64_t &elementSize, const size_t &indexCount, void *newData) :
    vk_buffer(elementSize * indexCount, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT),
    mIndexType(indexType),
    mIndexCount(static_cast<uint32_t>(indexCount)) {
    const auto logicalDevice = vk_core::instance().getDevice()->getDevice();

    // Copies the index data to the buffer.
    void *data;
    vkMapMemory(logicalDevice, mBufferMemory, 0, mSize, 0, &data);
    memcpy(data, newData, static_cast<size_t>(mSize));
    vkUnmapMemory(logicalDevice, mBufferMemory);
}

vk_indexBuffer::~vk_indexBuffer() {
}
