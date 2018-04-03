#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include "util.h"
#include "vkqueuefamilyindices.h"
class vk_device
{
public:
    vk_device(VkInstance instance ,VkSurfaceKHR surface) {
        PickPhysicalDevice(instance,surface);
        createLogicalDevice();
    }

    VkDevice getDevice(){return mDevice;}
    VkPhysicalDevice getPhysicalDevice(){return mPhyDevice;}
    vk_queueFamilyIndices getQueueFamilyIndices(){return mQueueFamilyIndices;}

    VkQueue getGraphicsQueue() const { assert(mGraphicsQueue); return mGraphicsQueue; }
    VkQueue getComputeQueue() const { assert(mComputeQueue); return mComputeQueue; }
    VkQueue getPresentQueue() const { assert(mPresentQueue); return mPresentQueue; }

private:
    void PickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
    void createLogicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);


    VkDevice mDevice;
    VkPhysicalDevice mPhyDevice;
    vk_queueFamilyIndices mQueueFamilyIndices;

    VkQueue mGraphicsQueue = VK_NULL_HANDLE;
    VkQueue mPresentQueue = VK_NULL_HANDLE;
    VkQueue mComputeQueue = VK_NULL_HANDLE;
};

#endif
