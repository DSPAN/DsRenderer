#ifndef UTIL_H
#define UTIL_H
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <memory>
#include <set>
#include <assert.h>
#include <glm/glm.hpp>

//class define
class vk_core;
class vk_device;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


bool checkValidationLayerSupport();
std::vector<const char*> getRequiredExtensions();

bool checkDeviceExtensionSupport(VkPhysicalDevice device);

//swap chain support
struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

VkShaderModule loadShader(const char *fileName, VkDevice device);

uint32_t findMemoryType(VkPhysicalDevice  physicalDevice,uint32_t typeFilter, VkMemoryPropertyFlags properties);

#endif // UTIL_H
