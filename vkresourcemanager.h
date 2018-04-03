#ifndef VK_RESOURCEMANAGER_H
#define VK_RESOURCEMANAGER_H
#include "util.h"
#include "vkdevice.h"
#include "vkbuffer.h"
#include "vkimage.h"
/*

//todo:remove../add create image
//todo:add commandpool,change std::shared_ptr..
typedef std::map< BufferHandle, std::shared_ptr<vk_buffer>> BufferHandleMap;
typedef std::map< ImageHandle, std::shared_ptr<vk_image>> ImageHandleMap;

class vk_resourceManager
{
public:
    vk_resourceManager(std::shared_ptr<vk_device> device) {
        mDevice = device;
        mNextBufferHandle = 0;
        mNextImageHandle = 0;
    }
    std::shared_ptr<vk_buffer> createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

    std::shared_ptr<vk_image> createImage();

    void addBufferHandle(std::shared_ptr<vk_buffer>& res);

    void addImageHandle(std::shared_ptr<vk_image>& res);

    BufferHandle getNextBufferHandle() { return mNextBufferHandle++;}

    ImageHandle getNextImageHandle() { return mNextImageHandle++;}

    void copyBuffer(std::shared_ptr<vk_buffer> src,std::shared_ptr<vk_buffer> dst,VkCommandBuffer commandBuffer);

private:
    std::shared_ptr<vk_device> mDevice;
    BufferHandleMap mMapBufferByHandle;
    BufferHandle mNextBufferHandle;
    ImageHandleMap mMapImageByHandle;
    ImageHandle mNextImageHandle;
};

*/
#endif // VKRESOURCEMANAGER_H
