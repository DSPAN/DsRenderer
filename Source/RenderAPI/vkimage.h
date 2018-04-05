#ifndef VK_IMAGE_H
#define VK_IMAGE_H
#include "util.h"
#include "vkcore.h"

void createImage(const uint32_t &width, const uint32_t &height, const VkFormat &format,const VkImageType &imageType, const VkImageTiling &tiling, const VkImageUsageFlags &usage, const VkMemoryPropertyFlags &properties, VkImage &image, VkDeviceMemory &imageMemory);

void setImageLayout(const VkImage &image, const VkImageLayout &oldLayout, const VkImageLayout &newLayout);

void copyBufferToImage(const uint32_t &width, const uint32_t &height, const VkBuffer &buffer, const VkImage &image);

class vk_image{
  public:
    vk_image(){
        mWidth = 0;
        mHeight = 0;
        mMipLevels = 1;
        mComponents = 0;
        mFormat = VK_FORMAT_R8G8B8A8_UNORM;
        mTiling = VK_IMAGE_TILING_OPTIMAL;
    }
    ~vk_image(){
        const auto logicalDevice = vk_core::instance().getDevice()->getDevice();
        vkDestroyImageView(logicalDevice, mImageView, nullptr);
        vkDestroyImage(logicalDevice, mImage, nullptr);
        vkFreeMemory(logicalDevice, mDeviceMemory, nullptr);
        vkDestroySampler(logicalDevice, mSampler, nullptr);
    }

    void updateDescriptor() {
        mDescriptor.sampler = mSampler;
        mDescriptor.imageView = mImageView;
        mDescriptor.imageLayout = mImageLayout;
    }

protected:
    VkImage mImage;
    VkImageView mImageView;
    VkDeviceMemory mDeviceMemory;
    VkImageLayout mImageLayout;
    VkDescriptorImageInfo mDescriptor;
    VkSampler mSampler;
    VkFormat mFormat;
    VkImageTiling mTiling;
    uint32_t mWidth, mHeight;
    uint32_t mMipLevels;
    uint32_t mComponents;
};

#endif // VKIMAGE_H
