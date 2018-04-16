#ifndef VK_CORE_H
#define VK_CORE_H
#include "util.h"
#include "../Utility/module.h"
#include "vkdevice.h"
#include "vkwindow.h"
#include "vkswapchain.h"

class vk_core :public Module<vk_core>
{
public:
    vk_core(std::shared_ptr<vk_device> device,std::shared_ptr<vk_swapChain> swapChain) {
        mDevice = device;
        mSwapChain = swapChain;
        createCommandPool();
    }

    std::shared_ptr<vk_device> getDevice(){return mDevice;}

    std::shared_ptr<vk_swapChain> getSwapChain(){return mSwapChain;}

    VkCommandPool getCommandPool(){return mCommandPool;}

    VkCommandBuffer createCommand();

    VkCommandBuffer beginSingleTimeCommands(const VkCommandBufferLevel &level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    void endSingleTimeCommands(const VkCommandBuffer &commandBuffer);

private:
    void createCommandPool();
private:
    std::shared_ptr<vk_device> mDevice;
    std::shared_ptr<vk_swapChain> mSwapChain;
    VkCommandPool mCommandPool;

};


#endif // VKCORE_H
