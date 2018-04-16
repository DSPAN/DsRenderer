#ifndef VK_IMAGE_H
#define VK_IMAGE_H
#include "util.h"
#include "vkcore.h"


class vk_image{
  public:
    vk_image(const uint32_t &width, const uint32_t &height, const VkFormat &format, const VkImageType &imageType, const VkImageTiling &tiling, const VkImageUsageFlags &usage, const VkMemoryPropertyFlags &properties, VkImageAspectFlags aspectFlags);

    ~vk_image(){
        clear();
    }

    VkImage getImage() const { return mImage; }

    VkImageView getImageView() const { return mImageView; }

    VkDeviceMemory getDeviceMemory() const { return mDeviceMemory; }

    static void setImageLayout(const VkImage &image, const VkFormat &format, const VkImageLayout &oldLayout, const VkImageLayout &newLayout);

    static void copyBufferToImage(const uint32_t &width, const uint32_t &height, const VkBuffer &buffer, const VkImage &image);

    void clear() {
        const auto logicalDevice = vk_core::instance().getDevice()->getDevice();
        vkDestroyImageView(logicalDevice, mImageView, nullptr);
        vkDestroyImage(logicalDevice, mImage, nullptr);
        vkFreeMemory(logicalDevice, mDeviceMemory, nullptr);
        if(mSampler != VK_NULL_HANDLE) {
            //vkDestroySampler(logicalDevice, mSampler, nullptr);
        }
    }

protected:
    VkImage mImage;
    VkImageView mImageView;
    VkDeviceMemory mDeviceMemory;
    VkImageLayout mImageLayout;
    VkSampler mSampler;
    VkFormat mFormat;
    VkImageTiling mTiling;
    uint32_t mWidth, mHeight;
    uint32_t mMipLevels;
    uint32_t mComponents;
};

#endif // VKIMAGE_H
