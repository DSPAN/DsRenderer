#include "Source/app.h"

int main() {
    App* app =new App(800,600);
    app->init();
    app->run();
    return 0;
}
