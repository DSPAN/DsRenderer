#include "app.h"
#include "ResourceManagers/meshmanager.h"
#include "Importer/importer.h"
#include "Input/input.h"
#include "./RenderAPI/vksurface.h"

App::App(int w,int h)
{
    mWidth=w;
    mHeight=h;
}
App::~App()
{
    vkDestroyInstance(mInstance, nullptr);
}
void App::init()
{
    //init window
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    mWindow = glfwCreateWindow(mWidth, mHeight, "dsRender", nullptr, nullptr);
    glfwSetWindowUserPointer(mWindow, this);

    //create instance
    createInstance();

    //create surface
    VkSurfaceKHR surface;
    auto res = glfwCreateWindowSurface(mInstance, mWindow, nullptr, &surface);
    if ( res != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }

    std::shared_ptr<vk_surface> surfacePtr = std::shared_ptr<vk_surface>(new vk_surface(surface));

    //create device
    std::shared_ptr<vk_device> devicePtr(new vk_device(mInstance,surfacePtr->getSurface()));

    //create swapChain
    std::shared_ptr<vk_swapChain> swapChainPtr(new vk_swapChain(devicePtr ,surfacePtr));
    VkExtent2D extent;
    extent.width = mWidth;
    extent.height = mHeight;
    swapChainPtr->reCreateSwapChain(extent);

    //vk_core start
    vk_core::startUp(devicePtr,swapChainPtr);
    MeshManager::startUp();
    Importer::startUp();
    Input::startUp();

    Importer::instance().loadMeshRes("E:/DsRenderer/DsRenderer/Data/Meshs/untitled.gltf");
    std::shared_ptr<Mesh> mesh = MeshManager::instance().getByHandle(0);
    std::cout<<"name : "<<mesh->mName<<std::endl;
    std::cout<<"vectex count : "<<mesh->vertexData.size()<<std::endl;
    std::cout<<"index count : "<<mesh->indexData.size()<<std::endl;

    mesh->setBuffer();
    mRenderer = std::shared_ptr<Renderer>(new Renderer());
    mRenderer->init();

    //window callback
    glfwSetFramebufferSizeCallback(mWindow, App::resizeCallback);
    glfwSetKeyCallback(mWindow, App::keyCallback);
    glfwSetMouseButtonCallback(mWindow, App::mouseButtonCallback);
    glfwSetCursorPosCallback(mWindow, App::cursorPosCallback);
    glfwSetScrollCallback(mWindow, App::mouseScrollCallback);
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
    while (!glfwWindowShouldClose(mWindow)) {
        Input::instance().tick();
        glfwPollEvents();
        mRenderer->update();
        mRenderer->drawFrame();
    }

    vkDeviceWaitIdle(vk_core::instance().getDevice()->getDevice());
}

void App::resize(int width, int height) {
    assert((0 <= width) && (0 <= height));
    mRenderer->resize(width,height);
}

void App::cursorPosEvent(double xPos, double yPos) {
    Input::instance().setMousePosition(glm::vec2(xPos, yPos));
}
void App::keyEvent(int key, int scancode, int action, int mods) {
    int curKey = 0;
    if(key >= 48&&key <= 57) {
        curKey = key - 48;
    }else if(key >= 65&&key <= 90) {
        curKey = key - 55;
    }else {
        return ;
    }

    switch (action) {
    case GLFW_PRESS :
        Input::instance().setKeyDown(curKey);
        Input::instance().setKey(curKey,true);
        break;
    case GLFW_RELEASE :
        Input::instance().setKeyUp(curKey);
        Input::instance().setKey(curKey,false);
        break;
    default:
        break;
    }
}
void App::mouseButtonEvent(int button, int action, int mods) {
    switch (action) {
    case GLFW_PRESS :
        Input::instance().setMouseButtonDown(button);
        Input::instance().setMouseButton(button,true);
        break;
    case GLFW_RELEASE :
        Input::instance().setMouseButtonUp(button);
        Input::instance().setMouseButton(button,false);
        break;
    default:
        break;
    }
}

void App::mouseScrollEvent(double xOffset, double yOffset) {
    Input::instance().setMouseScrollWheel(yOffset);
}

void App::resizeCallback(GLFWwindow *window, int width, int height) {
    App * app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    app->resize(width, height);
}

void App::cursorPosCallback(GLFWwindow * window, double xPos, double yPos) {
  App * app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
  app->cursorPosEvent(xPos, yPos);
}

void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  App * app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
  app->keyEvent(key, scancode, action, mods);
}

void App::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
  App * app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
  app->mouseButtonEvent(button, action, mods);
}

void App::mouseScrollCallback(GLFWwindow * window, double xOffset, double yOffset) {
  App * app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
  app->mouseScrollEvent(xOffset, yOffset);
}

