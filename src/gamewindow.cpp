#include <iostream>
#include <ctime>
#include <random>
#include "gamewindow.h"

GameWindow::GameWindow() {

    // Declaration
    //--------------------------------------------------------------------------------------------------------

    this->width = 1920;
    this->height = 991;

    this->title = "Deal Dash";

    this->loading = false;
    this->loadedResources = 0;

    //--------------------------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------------------------
    
    srand(time(NULL));
    InitWindow(this->width, this->height, this->title);
    InitAudioDevice();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    this->currentScreen = new HomeScreen(this->width, this->height);

    GameWindow::setIcon();

    //--------------------------------------------------------------------------------------------------------
    // Main Game Loop
    //--------------------------------------------------------------------------------------------------------

    while (!WindowShouldClose())    // Detect window close button or ESC key
        GameWindow::Update(), 
        GameWindow::Draw();

    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)
    CloseWindow();        // Close window and OpenGL context
    
    //--------------------------------------------------------------------------------------------------------

}

GameWindow::~GameWindow() {

    // De-Initialization
    //--------------------------------------------------------------------------------------------------------

    delete this->currentScreen;

    //--------------------------------------------------------------------------------------------------------

}

void GameWindow::Update() {

    //--------------------------------------------------------------------------------------------------------
    // Update Variables
    //--------------------------------------------------------------------------------------------------------

    int button = this->currentScreen->eventListener();

    if (button == 0)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    else if (button == -1)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

    else if (button == -2)
        SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);

    if (button == 1) {

        delete this->currentScreen;
        this->currentScreen = new HomeScreen(this->width, this->height);

    } else if (button == 2) {

        delete this->currentScreen;
        this->currentScreen = new SelectScreen(this->width, this->height);

    } else if (button == 3 || this->loading) {

        if (this->loading && this->tempScreen->deck->loadedResources.load() == 104) {

            delete this->currentScreen;
            this->tempScreen->GameStart();
            this->currentScreen = this->tempScreen;
            this->loading = false;

        } else if (!this->loading) {

            this->loading = true;
            this->tempScreen = new SpiderScreen(this->width, this->height);
            SelectScreen* temp = dynamic_cast<SelectScreen *>(this->currentScreen);

            delete temp->spiderButton;
            delete temp->classicButton;

            temp->spiderButton = nullptr;
            temp->classicButton = nullptr;

        }
    
    }

    //--------------------------------------------------------------------------------------------------------

}

void GameWindow::Draw() {


    //--------------------------------------------------------------------------------------------------------
    // Draw
    //--------------------------------------------------------------------------------------------------------

    BeginDrawing();

        ClearBackground(WHITE);

        this->currentScreen->Draw();

        if (this->loading)
            this->currentScreen->DrawLoading(this->tempScreen->deck->loadedResources.load());

    EndDrawing();

    //--------------------------------------------------------------------------------------------------------

}

void GameWindow::setIcon() {

    Image icon = LoadImage("assets/imgs/icon.png");

    SetWindowIcon(icon);
    UnloadImage(icon);

}