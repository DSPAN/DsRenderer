#ifndef APP_H
#define APP_H

#include "RenderAPI/vkwindow.h"
#include "RenderAPI/vkcore.h"
#include "Renderer/renderer.h"

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
    void reSize();
    static void onWindowResized(GLFWwindow* window,int width, int height);

    int width = 0;
    int height = 0;
    VkInstance mInstance;
    std::shared_ptr<vk_device> mDevice;
    std::shared_ptr<vk_window> mWindow;
    std::shared_ptr<Renderer> mRenderer;
};

#endif
