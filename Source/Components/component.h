#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Utility/rtti.h"
#include "json.hpp"
#include <memory>

class Entity;

enum COMPONENT_TYPE {
    STATIC_MODEL = 1,
    LIGHT = 2,
};

class Component :public Rtti
{
public:
    Component() {}

    const std::string& getRTTIName() override {
        static std::string name = "Component";
        return name;
    }

    uint32_t getRTTIId() override {
        return 0;
    }

    virtual void setEntity(std::shared_ptr<Entity> entity) {
        mEntity = entity;
    }

    std::shared_ptr<Entity> getEntity() {
        return mEntity;
    }

protected:
    std::shared_ptr<Entity> mEntity;
};
#endif // COMPOENT_H
