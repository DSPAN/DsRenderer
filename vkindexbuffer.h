#ifndef VK_INDEXBUFFER_H
#define VK_INDEXBUFFER_H
#include "vkbuffer.h"

class vk_indexBuffer :public vk_buffer
{
public:
    vk_indexBuffer(const VkIndexType &indexType, const uint64_t &elementSize, const size_t &indexCount, void *newData);

    ~vk_indexBuffer();

    VkIndexType getIndexType() const { return mIndexType; }

    uint32_t getIndexCount() const { return mIndexCount; }
private:
    VkIndexType mIndexType;
    uint32_t mIndexCount;
};

#endif // VKINDEXBUFFER_H
