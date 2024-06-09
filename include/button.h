#pragma once
#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"

class Button {

    protected:

        Vector2 position;
        Texture2D img;
        Sound sound;

    public:

        Button(Image image, Vector2 c) : position(c), img(LoadTextureFromImage(image)), sound(LoadSound("assets/sound/btn_clk.wav")) {}

        virtual ~Button() {

            UnloadTexture(img);
            // Commented it out as it unloaded the sound before it was played
            // Will need to add a transition to the sound to prevent it from being unloaded before it finishes playing
            // An option would be to create all screen objects at runtime and just change the current screen
            // UnloadSound(sound);

        }

        virtual void display() = 0;
        virtual bool isHovering() = 0;

        virtual int isClicked() {

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && this->isHovering()) {
                PlaySound(sound);
                return true;
            }
            
            return false;

        }

};

class CircularButton : public Button {

    float radius;

    public:

        CircularButton(Image& image, Vector2 pos, int r) : Button(image, pos), radius(r) {}

        void display() override {

            Vector2 newPos = Vector2Subtract(position, Vector2{ radius, radius });

            DrawTextureV(img, newPos, WHITE);

        }

        bool isHovering() override {
            return (Vector2Distance(GetMousePosition(), position) <= this->radius);
        }

};

class RectangularButton : public Button {

    protected:

        float width;
        float height;

    public:

        RectangularButton(Image& image, Vector2 pos, int w, int h) : Button(image, pos), width(w), height(h) {}

        virtual void display() override {
            DrawTextureV(this->img, this->position, WHITE);
        }

        bool isHovering() override {
            return ((GetMouseX() >= this->position.x) && (GetMouseX() <= this->position.x + this->width) && (GetMouseY() >= this->position.y) && (GetMouseY() <= this->position.y + this->height));
        }

};