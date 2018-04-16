#ifndef APP_H
#define APP_H

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
    void resize(int width, int height);
    void cursorPosEvent(double xPos, double yPos);
    void keyEvent(int key, int scancode, int action, int mods);
    void mouseButtonEvent(int button, int action, int mods);

    static void paintCallback(GLFWwindow *window);
    static void resizeCallback(GLFWwindow *window, int width, int height);
    static void cursorPosCallback(GLFWwindow * window, double xPos, double yPos);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
private:
    void createInstance();
    void setupDebugCallback();
    void mainLoop();
    void drawFrame();
    void resize();

    int mWidth = 0;
    int mHeight = 0;
    VkInstance mInstance;
    GLFWwindow* mWindow;
    std::shared_ptr<Renderer> mRenderer;
};

#endif
