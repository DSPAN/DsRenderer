#ifndef ENTITY_H
#define ENTITY_H

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "../Components/component.h"
#include <memory>

class Entity{
public:
    Entity() {

    }

    glm::mat4 getWorldMatrix() {
        return glm::translate(glm::mat4(1.0f), mPos) * glm::toMat4(mRot) * glm::scale(glm::mat4(1.0f), mScale);
    }

    glm::vec3 mPos;
    glm::quat mRot;
    glm::vec3 mScale;

    void addComp(std::shared_ptr<Component> comp) {
        for(uint32_t i =0;i < mComponents.size();i++) {
            if(comp->getRTTIId() == mComponents[i]->getRTTIId()) {
                std::cout<<"this component has already exist!"<<std::endl;
                return ;
            }
        }
        comp->setEntity(std::shared_ptr<Entity>(this));
        mComponents.push_back(comp);
    }

    std::shared_ptr<Component> getComp(COMPONENT_TYPE compType) {
        for(uint32_t i =0;i < mComponents.size();i++) {
            if(mComponents[i]->getRTTIId() == compType) {
                return mComponents[i];
            }
        }
        std::cout<<"this entiry has't exist!"<<std::endl;
        return nullptr;
    }

private:
    std::vector<std::shared_ptr<Component>> mComponents;

};

#endif // ENTITY_H
