#include "vkdevice.h"

void vk_device::PickPhysicalDevice(VkInstance instance,VkSurfaceKHR surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (auto device : devices) {
        if (isDeviceSuitable(device, surface)) {
            mPhyDevice = device;
            return;
        }
    }

    throw std::runtime_error("failed to find a suitable GPU!");
}

bool vk_device::isDeviceSuitable(VkPhysicalDevice physicalDevice ,VkSurfaceKHR surface) {
    mQueueFamilyIndices.clear();
    mQueueFamilyIndices.findQueueFamilies(physicalDevice, surface,VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);

    bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    auto isQueueFamilyIndicesComplete = [this]() {
        return mQueueFamilyIndices.graphicsFamily >= 0 &&
            mQueueFamilyIndices.presentFamily >= 0 &&
            mQueueFamilyIndices.computeFamily >= 0;
    };

    return isQueueFamilyIndicesComplete() && extensionsSupported && swapChainAdequate;
}

void vk_device::createLogicalDevice() {
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<int> uniqueQueueFamilies = {
        mQueueFamilyIndices.graphicsFamily,
        mQueueFamilyIndices.computeFamily,
        mQueueFamilyIndices.presentFamily
    };

    float queuePriority = 1.0f;
    for (int queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    //?
    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(mPhyDevice, &createInfo, nullptr, &mDevice) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(mDevice, mQueueFamilyIndices.graphicsFamily, 0, &mGraphicsQueue);
    vkGetDeviceQueue(mDevice, mQueueFamilyIndices.presentFamily, 0, &mPresentQueue);
    vkGetDeviceQueue(mDevice, mQueueFamilyIndices.computeFamily, 0, &mComputeQueue);
}
