#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../RenderAPI/vkimage.h"
#include <memory>

typedef unsigned long long int Handle;

class Texture2D {
public:
    Texture2D() {

    }

    std::string mName;
    Handle mHandle;
    std::shared_ptr<vk_image> mImage;
};

typedef std::shared_ptr<Texture2D> TexturePtr;

#endif // TEXTURE2D_H
