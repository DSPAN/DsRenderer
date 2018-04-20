#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include "../Utility/module.h"
#include "staticmodel.h"

class RenderScene :public Module<RenderScene> {
public:
    RenderScene() {
        mNextHandle = 0;
    }

    virtual ~RenderScene() {
        removeAll();
    }

    Handle getNextHandle() {
        return mNextHandle++;
    }

    void removeAll(void) {
        mStaticModelMap.clear();
    }

    StaticModelPtr addStaticModel() {
        StaticModelPtr res = StaticModelPtr(new StaticModel());
        res->mHandle = getNextHandle();

        addStaticModelIpm(res);

        return res;
    }

    void removeStaticModel(Handle handle) {
        StaticModelPtr res = getStaticModel(handle);

        if (res) {
            removeStaticModelIpm(res);
        }
    }

    StaticModelPtr getStaticModel(Handle handle) {
        StaticModelPtr res;
        std::map< Handle, StaticModelPtr>::iterator handleIt = mStaticModelMap.find(handle);
        if (handleIt != mStaticModelMap.end()) {
            res = handleIt->second;
        }
        return res;
    }

    bool staticModelExists(Handle handle) {
        if(getStaticModel(handle)) {
            return true;
        }
        return false;
    }

private:
    void addStaticModelIpm( StaticModelPtr& res) {
        std::pair<std::map< Handle, StaticModelPtr>::iterator, bool> resultHandle =
            mStaticModelMap.insert( std::map< Handle, StaticModelPtr>::value_type( res->mHandle, res ) );
        if (!resultHandle.second) {
            std::cout<<"Res has already exist!"<<std::endl;
        }
    }

    void removeStaticModelIpm( StaticModelPtr& res ) {
        std::map< Handle, StaticModelPtr>::iterator handleIt = mStaticModelMap.find(res->mHandle);
        if (handleIt != mStaticModelMap.end()) {
            mStaticModelMap.erase(handleIt);
        }
    }

private:
    std::map< Handle, StaticModelPtr> mStaticModelMap;
    Handle mNextHandle;

};

#endif // RENDER_SCENE_H
