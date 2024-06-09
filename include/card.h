#pragma once
#include "raylib.h"
#include <string>

#define CARD_WIDTH 150
#define CARD_HEIGHT 213


// odd numbers are black, even numbers are red
enum Suit {

    SPADES = 1,
    HEARTS = 2,
    CLUBS = 3,
    DIAMONDS = 4

};

class Card {

    int rank;
    Suit suit;
    bool hidden;
    Image img;
    Texture2D cardImage;

    public:
    
        Card(int, Suit, std::string);
        ~Card();

        Suit getSuit();
        int getRank();
        
        bool isHidden();
        void showCard();
        
        Card operator-(int);
        bool operator==(const Card&);
        bool operator!=(const Card&);

        void loadImage();
        void displayCard(float, float);

};