#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture2d.h"
#include "../RenderAPI/vkcore.h"

class Material {
public:
    Material() {

    }

    void createDescriptorSet() {
    }

    std::shared_ptr<Texture2D> mDiffuseTex;
    VkDescriptorSet mDescSet;
};

#endif // MATERIAL_H
