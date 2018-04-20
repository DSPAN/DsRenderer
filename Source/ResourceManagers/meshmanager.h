#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H
#include "../Resources/mesh.h"
#include "../Utility/module.h"
#include <map>

typedef std::map< MeshHandle, MeshPtr>	MeshHandleMap;
typedef std::map< std::string, MeshPtr>	MeshNameMap;

class MeshManager :public Module<MeshManager> {
public:
    MeshManager():mNextHandle(0){}

    virtual ~MeshManager() {
        removeAll();
    }

    MeshHandle getNextHandle() {
        return mNextHandle++;
    }

    virtual void remove(const std::string& name) {

        MeshPtr res = getByName(name);
        if (res) {
            removeMesh(res);
        }
    }

    virtual void remove(MeshHandle handle) {
        MeshPtr res = getByHandle(handle);

        if (res) {
            removeMesh(res);
        }
    }

    virtual void removeAll(void) {
        mMapResources.clear();
        mMapResourcesByHandle.clear();
    }

    virtual MeshPtr getByName(const std::string& name) {
        std::string uniqueName(name);
        MeshPtr res;
        MeshNameMap::iterator nameIt = mMapResources.find(uniqueName);
        if (nameIt != mMapResources.end()) {
            res = nameIt->second;
        }
        return res;
    }

    virtual MeshPtr getByHandle(MeshHandle handle) {
        MeshPtr res;
        MeshHandleMap::iterator handleIt = mMapResourcesByHandle.find(handle);
        if (handleIt != mMapResourcesByHandle.end()) {
            res = handleIt->second;
        }
        return res;
    }

    virtual bool resourceExists(const std::string& name) {
        if(getByName(name)) {
            return true;
        }
        return false;
    }

    virtual bool resourceExists(MeshHandle handle) {
        if(getByHandle(handle)) {
            return true;
        }
        return false;
    }

    virtual void addMesh( MeshPtr& res) {
        std::pair<MeshNameMap::iterator, bool> result;
        result = mMapResources.insert( MeshNameMap::value_type( res->mName, res ) );

        std::pair<MeshHandleMap::iterator, bool> resultHandle =
            mMapResourcesByHandle.insert( MeshHandleMap::value_type( res->mHandle, res ) );
        if (!resultHandle.second) {
            std::cout<<"Res has already exist!"<<std::endl;
        }
    }

    virtual void removeMesh( MeshPtr& res ) {
        MeshNameMap::iterator nameIt = mMapResources.find(res->mName);
        if (nameIt != mMapResources.end()) {
            mMapResources.erase(nameIt);
        }

        MeshHandleMap::iterator handleIt = mMapResourcesByHandle.find(res->mHandle);
        if (handleIt != mMapResourcesByHandle.end()) {
            mMapResourcesByHandle.erase(handleIt);
        }
    }

protected:
    MeshHandleMap mMapResourcesByHandle;
    MeshNameMap mMapResources;
    MeshHandle mNextHandle;
};

#endif // MESH_MANAGER_H
