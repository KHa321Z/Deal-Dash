#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include "button.h"
#include "pile.h"
#include "deck.h"

class Screen {

    protected:

        float width;
        float height;

        std::string imgPath;
        std::string soundPath;

        Texture2D background;

    public:

        Screen(float w, float h, bool main) : width(w), height(h), imgPath("assets/imgs/"), soundPath("assets/sound/"), background(LoadTexture((imgPath + (main ? "main" : "game") + "_bg.png").c_str())) {}

        virtual ~Screen() {
            UnloadTexture(background);
        }

        virtual void Draw() {
            DrawTexture(background, 0, 0, WHITE);
        };
        virtual void DrawLoading(int) {};

        virtual int eventListener() = 0;


};

class HomeScreen : public Screen {

    public:
    
        Texture2D title;
        CircularButton* playButton;
        CircularButton* settingsButton;
        CircularButton* userButton;

        HomeScreen(float, float);
        ~HomeScreen();

        virtual void Draw() override;

        int eventListener() override;

};

class SelectScreen : public Screen {

    public:

        Texture2D title;

        Font loadingFont;
        const char* loadingText;

        RectangularButton* spiderButton;
        RectangularButton* classicButton;
        CircularButton* homeButton;

        SelectScreen(float, float);
        virtual ~SelectScreen();

        virtual void Draw() override;
        virtual void DrawLoading(int) override;

        int eventListener() override;

};

class SpiderScreen : public Screen {

    bool win;
    Texture2D winImage;
    Sound winSound;
    Sound invalidSound;

    Font scoreFont;
    const char* score;
    int scoreValue;

    Pile* previousPile;
    std::vector<Pile *> piles;
    std::vector<Card *> selectedCards;

    public:

        CircularButton* homeButton;
        CircularButton* settingsButton;
        Deck* deck;

        SpiderScreen(float, float);
        virtual ~SpiderScreen();

        void GameStart();

        virtual void Draw() override;

        int eventListener() override;

};

class ClassicScreen : public Screen {

    public:

        CircularButton* homeButton;
        CircularButton* settingsButton;

        std::string score;
        int scoreValue;

        //std::vector<Pile> piles;

        ClassicScreen(float, float);
        virtual ~ClassicScreen();

        virtual void Draw() override;

        int eventListener() override;

};