#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../RenderAPI/vkimage.h"
#include <memory>

class Texture2D {
public:
    Texture2D() {

    }

    std::shared_ptr<vk_image> mImage;
};



#endif // TEXTURE2D_H
