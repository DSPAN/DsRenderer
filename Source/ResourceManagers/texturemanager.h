#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../Resources/texture2d.h"
#include <map>

typedef std::map< Handle, TexturePtr>	TextureHandleMap;
typedef std::map< std::string, TexturePtr>	TextureNameMap;

class TextureManager :public Module<TextureManager> {
public:
    TextureManager():mNextHandle(0){}

    virtual ~TextureManager() {
        removeAll();
    }

    Handle getNextHandle() {
        return mNextHandle++;
    }

    virtual void remove(const std::string& name) {

        TexturePtr res = getByName(name);
        if (res) {
            removeTexture(res);
        }
    }

    virtual void remove(Handle handle) {
        TexturePtr res = getByHandle(handle);

        if (res) {
            removeTexture(res);
        }
    }

    virtual void removeAll(void) {
        mMapResources.clear();
        mMapResourcesByHandle.clear();
    }

    virtual TexturePtr getByName(const std::string& name) {
        std::string uniqueName(name);
        TexturePtr res;
        TextureNameMap::iterator nameIt = mMapResources.find(uniqueName);
        if (nameIt != mMapResources.end()) {
            res = nameIt->second;
        }
        return res;
    }

    virtual TexturePtr getByHandle(Handle handle) {
        TexturePtr res;
        TextureHandleMap::iterator handleIt = mMapResourcesByHandle.find(handle);
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

    virtual bool resourceExists(Handle handle) {
        if(getByHandle(handle)) {
            return true;
        }
        return false;
    }

    virtual void addTexture( TexturePtr& res) {
        std::pair<TextureNameMap::iterator, bool> result;
        result = mMapResources.insert( TextureNameMap::value_type( res->mName, res ) );

        std::pair<TextureHandleMap::iterator, bool> resultHandle =
            mMapResourcesByHandle.insert( TextureHandleMap::value_type( res->mHandle, res ) );
        if (!resultHandle.second) {
            std::cout<<"Res has already exist!"<<std::endl;
        }
    }

    virtual void removeTexture( TexturePtr& res ) {
        TextureNameMap::iterator nameIt = mMapResources.find(res->mName);
        if (nameIt != mMapResources.end()) {
            mMapResources.erase(nameIt);
        }

        TextureHandleMap::iterator handleIt = mMapResourcesByHandle.find(res->mHandle);
        if (handleIt != mMapResourcesByHandle.end()) {
            mMapResourcesByHandle.erase(handleIt);
        }
    }

protected:
    TextureHandleMap mMapResourcesByHandle;
    TextureNameMap mMapResources;
    Handle mNextHandle;
};

#endif // TEXTURE_MANAGER_H
