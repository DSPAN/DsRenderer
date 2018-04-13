#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H
#include "vkdevice.h"
#include "vkwindow.h"
#include "util.h"

class vk_swapChain
{
public:
    vk_swapChain(std::shared_ptr<vk_device> device ,std::shared_ptr<vk_window> window) {
        mDevice=device;
        mWindow=window;
    }
    ~vk_swapChain() {

    }

    VkSwapchainKHR getSwapChain(){return mSwapChain;}

    const std::vector<VkImageView> &getImageViews() const{
        return mSwapChainImageViews;
    }

    VkExtent2D getSwapChainExtent(){return mSwapChainExtent;}

    VkFormat getSwapChainFormat(){return mSwapChainImageFormat;}

    void reCreateSwapChain();

private:
    void createSwapChain();

    void createSwapChainImageViews();

    void cleanUp();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    std::shared_ptr<vk_device> mDevice;
    std::shared_ptr<vk_window> mWindow;
    VkSwapchainKHR mSwapChain;
    std::vector<VkImage> mSwapChainImages;
    std::vector<VkImageView> mSwapChainImageViews;
    VkFormat mSwapChainImageFormat;
    VkExtent2D mSwapChainExtent;
};

#endif
