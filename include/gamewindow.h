#pragma once
#include <string>
#include "raylib.h"
#include "screens.h"

class GameWindow {

    float width;
    float height;

    const char* title;

    bool loading;
    int loadedResources;
    Screen* currentScreen;
    SpiderScreen* tempScreen;

    public:

        GameWindow();
        ~GameWindow();

        void Update();

        void Draw();

        void close();

        bool shouldClose();

        void setIcon();

};