#include "vkswapchain.h"
#include <limits>

void vk_swapChain::reCreateSwapChain() {
    createSwapChain();
    createSwapChainImageViews();
}

void vk_swapChain::createSwapChain() {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(mDevice->getPhysicalDevice(), mWindow->getSurface());

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount){
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = mWindow->getSurface();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    const vk_queueFamilyIndices &indices = mDevice->getQueueFamilyIndices();
    uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

    if (indices.graphicsFamily != indices.presentFamily){
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    VkSwapchainKHR oldSwapChain = mSwapChain;
    createInfo.oldSwapchain = oldSwapChain;

    VkSwapchainKHR newSwapChain;
    if (vkCreateSwapchainKHR(mDevice->getDevice(), &createInfo, nullptr, &newSwapChain) != VK_SUCCESS){
        throw std::runtime_error("failed to create swap chain!");
    }

    mSwapChain = newSwapChain;

    vkGetSwapchainImagesKHR(mDevice->getDevice(), mSwapChain, &imageCount, nullptr);
    m_swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(mDevice->getDevice(), mSwapChain, &imageCount, m_swapChainImages.data());

    mSwapChainImageFormat = surfaceFormat.format;
    mSwapChainExtent = extent;

}

void vk_swapChain::createSwapChainImageViews() {

}

VkSurfaceFormatKHR vk_swapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    }

    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR vk_swapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes){
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D vk_swapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {

    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        uint32_t width, height;
        mWindow->getExtent(width, height);
        VkExtent2D actualExtent = { width, height };

        actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}
