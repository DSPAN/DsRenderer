#ifndef VK_IMAGE_H
#define VK_IMAGE_H
#include "util.h"

typedef unsigned long long int ImageHandle;

struct vk_image
{
    vk_image(ImageHandle handle){
        mHandle = handle;
    }
    ImageHandle mHandle;
    VkImage mBuffer;
    VkImageView mImageView;
};

#endif // VKIMAGE_H
