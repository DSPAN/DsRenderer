#ifndef STATIC_MODEL_COMPONENT_H
#define STATIC_MODEL_COMPONENT_H

#include "component.h"
#include "../Renderer/renderscene.h"

class StaticModelComponent :public Component {
public:
    StaticModelComponent() {
        mStaticModel = RenderScene::instance().addStaticModel();
    }

    const std::string& getRTTIName() override {
        static std::string name = "StaticModelComponent";
        return name;
    }

    uint32_t getRTTIId() override {
        return COMPONENT_TYPE::STATIC_MODEL;
    }

    void setMesh(MeshPtr mesh) {
        mStaticModel->mMesh = mesh;
    }

    void setEntity(std::shared_ptr<Entity> entity) override {
        mEntity = entity;
        mStaticModel->mEntity = entity;
    }

private:
    StaticModelPtr mStaticModel;

};

#endif // STATIC_MODEL_COMPONENT_H
