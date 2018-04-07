#ifndef VK_WINDOW_H
#define VK_WINDOW_H
#include "util.h"

class vk_window
{
public:
    vk_window(void* app ,uint32_t w ,uint32_t h);
    ~vk_window();

    VkSurfaceKHR getSurface(){return mSurface;}
    void getExtent(uint32_t &width, uint32_t &height){
        width = mWidth;
        height = mHeight;
    }
    void createSurface(VkInstance instance);
    void initWindow();
    bool shouldClose();
    void pollEvents();
protected:
    void* mApp;
    uint32_t mWidth,mHeight;
    GLFWwindow* mWindow;
    VkSurfaceKHR mSurface;

};
#endif
