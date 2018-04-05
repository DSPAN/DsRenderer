#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "vkimage.h"

class Texture2D :public vk_image
{
public:
    Texture2D() {
        vk_image();
    }
    ~Texture2D(){}

    void load(const char* fileName);

    void setFormat(const VkFormat& format) {
        mFormat = format;
    }


private:
    void createImage();
    void createImageView();
    void createTextureSampler();


};


#endif // TEXTURE2D_H
