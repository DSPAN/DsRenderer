#ifndef INPUT_H
#define INPUT_H

#include "../Utility/module.h"
#include "keycode.h"
#include <memory.h>

class Input :public Module<Input> {
public:
    Input () {

    }

    void tick() {
        memset(mKeyDown,0,sizeof(mKeyDown));
        memset(mKeyUp,0,sizeof(mKeyUp));
        memset(mMouseButtonDown,0,sizeof(mMouseButtonDown));
        memset(mMouseButtonUp,0,sizeof(mMouseButtonUp));
    }

    void getKey(KeyCode key) {
        return mKey[(int)key];
    }

    void getKeyDown(KeyCode key) {
        return mKeyDown[(int)key];
    }

    void getKeyUp(KeyCode key) {
        return mKeyUp[(int)key];
    }

    void getMouseButton(MouseButton mouse) {
        return mMouseButtonHeld[(int)mouse];
    }

    void getMouseButtonDown(MouseButton mouse) {
        return mMouseButtonDown[(int)mouse];
    }

    void getMouseButtonUp(MouseButton mouse) {
        return mMouseButtonUp[(int)mouse];
    }

    void setMouseButton(int idx, bool state) {
        if(idx > 2||idx < 0) {
            return;
        }
        mMouseButtonHeld[idx] = state;
    }

    void setMouseButtonDown(int idx) {
        if(idx > 2||idx < 0) {
            return;
        }
        mMouseButtonDown[idx] = true;
    }

    void setMouseButtonUp(int idx) {
        if(idx > 2||idx < 0) {
            return;
        }
        mMouseButtonUp[idx] = true;
    }

    void setKey(int idx, bool state) {
        if(idx > ((int) KeyCode::Count) - 1||idx < 0) {
            return;
        }

        mKey[idx] = state;
    }

    void setKeyDown(int idx) {
        if(idx > ((int) KeyCode::Count) - 1||idx < 0) {
            return;
        }

        mKeyDown[idx] = true;
    }

    void setKeyUp(int idx) {
        if(idx > ((int) KeyCode::Count) - 1||idx < 0) {
            return;
        }

        mKeyUp[idx] = true;
    }

private:
    bool mMouseButtonHeld[3];
    bool mMouseButtonDown[3];
    bool mMouseButtonUp[3];
    bool mKeyDown[(int) KeyCode::Count];
    bool mKey[(int) KeyCode::Count];
    bool mKeyUp[(int) KeyCode::Count];
};

#endif // INPUT_H
