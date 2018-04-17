#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H
#include "vkdevice.h"
#include "vksurface.h"
#include "util.h"

class vk_swapChain
{
public:
    vk_swapChain(std::shared_ptr<vk_device> device ,std::shared_ptr<vk_surface> surface) {
        mDevice=device;
        mSurface=surface;
    }
    ~vk_swapChain() {

    }

    VkSwapchainKHR getSwapChain(){return mSwapChain;}

    const std::vector<VkImageView> &getImageViews() const{
        return mSwapChainImageViews;
    }

    VkExtent2D getSwapChainExtent(){return mSwapChainExtent;}

    VkFormat getSwapChainFormat(){return mSwapChainImageFormat;}

    void reCreateSwapChain(const VkExtent2D& extent);

private:
    void createSwapChain();

    void createSwapChainImageViews();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    //VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    std::shared_ptr<vk_device> mDevice;
    std::shared_ptr<vk_surface> mSurface;
    VkSwapchainKHR mSwapChain;
    std::vector<VkImage> mSwapChainImages;
    std::vector<VkImageView> mSwapChainImageViews;
    VkFormat mSwapChainImageFormat;
    VkExtent2D mSwapChainExtent;
};

#endif
