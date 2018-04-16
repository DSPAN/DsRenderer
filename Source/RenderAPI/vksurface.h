#ifndef VK_SURFACE_H
#define VK_SURFACE_H

#include "util.h"
#include <memory>

class vk_surface
{
public:
    vk_surface(VkSurfaceKHR surface) {
        mSurface = surface;
    }

    VkSurfaceKHR getSurface() {
        return mSurface;
    }

private:
    VkSurfaceKHR mSurface;
};

#endif // VKSURFACE_H
