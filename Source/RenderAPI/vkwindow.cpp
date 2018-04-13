#include "vkwindow.h"

vk_window::vk_window(void* app ,uint32_t w,uint32_t h) {
    mWidth = w;
    mHeight = h;
    mApp = app;
}

vk_window::~vk_window() {

}

void vk_window::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    mWindow = glfwCreateWindow(mWidth, mHeight, "dsRender", nullptr, nullptr);
    if (mApp) glfwSetWindowUserPointer(mWindow, mApp);
}

void vk_window::createSurface(VkInstance instance) {
    //check
    auto res = glfwCreateWindowSurface(instance, mWindow, nullptr, &mSurface);
    if ( res != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void vk_window::setWindowSizeCallBack(GLFWwindowsizefun onWindowResized) {
    glfwSetWindowSizeCallback(mWindow, onWindowResized);
}

bool vk_window::shouldClose() {
    return glfwWindowShouldClose(mWindow);
}

void vk_window::pollEvents() {
    glfwPollEvents();
}
