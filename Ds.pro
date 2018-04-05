QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    vkdevice.h \
    app.h \
    util.h \
    vkswapchain.h \
    vkwindow.h \
    vkqueuefamilyindices.h \
    renderer.h \
    vkbuffer.h \
    mesh.h \
    vkresourcemanager.h \
    vkimage.h \
    module.h \
    vkcore.h \
    vkvertexbuffer.h \
    vkindexbuffer.h \
    texture2d.h \
    stb_image.h \
    Source/RenderAPI/util.h \
    Source/RenderAPI/vkbuffer.h \
    Source/RenderAPI/vkcore.h \
    Source/RenderAPI/vkdevice.h \
    Source/RenderAPI/vkimage.h \
    Source/RenderAPI/vkindexbuffer.h \
    Source/RenderAPI/vkqueuefamilyindices.h \
    Source/RenderAPI/vkresourcemanager.h \
    Source/RenderAPI/vkswapchain.h \
    Source/RenderAPI/vkvertexbuffer.h \
    Source/RenderAPI/vkwindow.h \
    Source/Renderer/renderer.h \
    Source/Resources/mesh.h \
    Source/Resources/texture2d.h \
    Source/Utility/module.h \
    Source/Utility/stb_image.h \
    Source/app.h

SOURCES += main.cpp \
    app.cpp \
    util.cpp \
    vkdevice.cpp \
    vkswapchain.cpp \
    vkwindow.cpp \
    renderer.cpp \
    vkresourcemanager.cpp \
    vk_core.cpp \
    vkbuffer.cpp \
    vkvertexbuffer.cpp \
    vkindexbuffer.cpp \
    vkimage.cpp \
    texture2d.cpp \
    Examples/main.cpp \
    Source/RenderAPI/util.cpp \
    Source/RenderAPI/vk_core.cpp \
    Source/RenderAPI/vkbuffer.cpp \
    Source/RenderAPI/vkdevice.cpp \
    Source/RenderAPI/vkimage.cpp \
    Source/RenderAPI/vkindexbuffer.cpp \
    Source/RenderAPI/vkresourcemanager.cpp \
    Source/RenderAPI/vkswapchain.cpp \
    Source/RenderAPI/vkvertexbuffer.cpp \
    Source/RenderAPI/vkwindow.cpp \
    Source/Renderer/renderer.cpp \
    Source/Resources/texture2d.cpp \
    Source/app.cpp

INCLUDEPATH += "E:\DsRenderer\GLFW\glfw-3.2.1.bin.WIN32\include"
INCLUDEPATH += "D:\vulkan\1.0.68.0\Include"
INCLUDEPATH += "D:\glm\glm-master"




win32: LIBS += -LD:/vulkan/1.0.68.0/Lib32/ -lvulkan-1
INCLUDEPATH += D:/vulkan/1.0.68.0/Lib32
DEPENDPATH += D:/vulkan/1.0.68.0/Lib32


win32: LIBS += -L$$PWD/../GLFW/glfw-3.2.1.bin.WIN32/lib-mingw/ -lglfw3dll
INCLUDEPATH += $$PWD/../GLFW/glfw-3.2.1.bin.WIN32/lib-mingw
DEPENDPATH += $$PWD/../GLFW/glfw-3.2.1.bin.WIN32/lib-mingw
