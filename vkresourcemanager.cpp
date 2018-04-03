#include "vkresourcemanager.h"

std::shared_ptr<vk_buffer> vk_resourceManager::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
    std::shared_ptr<vk_buffer> ret(new vk_buffer(getNextBufferHandle()));

    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mDevice->getDevice(), &bufferInfo, nullptr, &ret->mBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mDevice->getDevice(), ret->mBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(mDevice->getPhysicalDevice(),memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(mDevice->getDevice(), &allocInfo, nullptr, &ret->mBufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(mDevice->getDevice(), ret->mBuffer, ret->mBufferMemory, 0);

    addBufferHandle(ret);
    return ret;
}

void vk_resourceManager::addBufferHandle(std::shared_ptr<vk_buffer>& res) {
    std::pair<BufferHandleMap::iterator, bool> resultHandle =
    mMapBufferByHandle.insert( BufferHandleMap::value_type( res->mHandle, res));

    if (!resultHandle.second){
        //error
    }
}

void vk_resourceManager::addImageHandle(std::shared_ptr<vk_image>& res){
    std::pair<ImageHandleMap::iterator, bool> resultHandle =
    mMapImageByHandle.insert( ImageHandleMap::value_type( res->mHandle, res));

    if (!resultHandle.second){
        //error
    }
}

