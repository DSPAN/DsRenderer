#ifndef APP_H
#define APP_H

#include "util.h"
#include "vkwindow.h"
#include "vkswapchain.h"
#include "vkcore.h"

class App
{
public:
    App(int w,int h);
    ~App();
    void init();
    void run();
private:
    void createInstance();
    void setupDebugCallback();
    void mainLoop();
    void drawFrame();

    int width = 0;
    int height = 0;
    VkInstance mInstance;
    std::shared_ptr<vk_device> mDevice;
    std::shared_ptr<vk_window> mWindow;
};

#endif
