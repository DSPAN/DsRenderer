#include"vkvertexbuffer.h"
#include"vkcore.h"

vk_vertexBuffer::vk_vertexBuffer(const uint64_t &elementSize, const size_t &vertexCount, void *newData) :
    vk_buffer(elementSize * vertexCount, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT),
    mVertexCount(static_cast<uint32_t>(vertexCount)) {
    const auto logicalDevice = vk_core::instance().getDevice()->getDevice();

    void *data;
    vkMapMemory(logicalDevice, mBufferMemory, 0, mSize, 0, &data);
    memcpy(data, newData, static_cast<size_t>(mSize));
    vkUnmapMemory(logicalDevice, mBufferMemory);
}

vk_vertexBuffer::~vk_vertexBuffer() {
}
