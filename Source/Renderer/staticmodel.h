#ifndef STATIC_MODEL_H
#define STATIC_MODEL_H

#include "../Resources/mesh.h"
#include <memory>

typedef unsigned long long int Handle;
class Entity;

class StaticModel{
public:
    StaticModel() {
        mHandle = -1;
    }

    Handle mHandle;
    MeshPtr mMesh;
    std::shared_ptr<Entity> mEntity;

};

typedef std::shared_ptr<StaticModel> StaticModelPtr;

#endif // STATIC_MODEL_H
