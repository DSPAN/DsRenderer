#include "app.h"


App::App(int w,int h)
{
    width=w;
    height=h;
}
App::~App()
{
    vkDestroyInstance(mInstance, nullptr);
}
void App::init()
{
    vk_window* _window = new vk_window(this,width,height);
    mWindow = std::shared_ptr<vk_window>(_window);
    mWindow->initWindow();
    createInstance();
    mWindow->createSurface(mInstance);

    vk_device* _device =new vk_device(mInstance,mWindow->getSurface());
    mDevice = std::shared_ptr<vk_device>(_device);

    vk_core::startUp(mDevice,mWindow);
}


void App::createInstance()
{
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "DsRenderer";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "DsEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void App::run() {
    mainLoop();
}

void App::mainLoop() {
    while (!mWindow->shouldClose()) {
        mWindow->pollEvents();
        drawFrame();

    }

    vkDeviceWaitIdle(mDevice->getDevice());
}

void App::drawFrame() {

}

