#ifndef VK_VERTEXBUFFER_H
#define VK_VERTEXBUFFER_H
#include "vkbuffer.h"

class vk_vertexBuffer:public vk_buffer
{
public:
    vk_vertexBuffer(const uint64_t &elementSize, const size_t &vertexCount, void *newData);
    ~vk_vertexBuffer();
    uint32_t getVertexCount() const { return mVertexCount; }
private:
    uint32_t mVertexCount;

};


#endif // VKVERTEXBUFFER_H
