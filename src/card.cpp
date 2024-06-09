#include <iostream>
#include "card.h"

Card::Card(int r, Suit s, std::string imgPath) : rank(r), suit(s), hidden(true), img(LoadImage(imgPath.c_str())) {
    ImageResize(&this->img, CARD_WIDTH, CARD_HEIGHT);
}

Card::~Card() {
    UnloadImage(this->img);
    UnloadTexture(this->cardImage);
}

Suit Card::getSuit() {
    return suit;
}

int Card::getRank() {
    return rank;
}

bool Card::isHidden() {
    return this->hidden;
}

void Card::showCard() {
    this->hidden = false;
}

Card Card::operator-(int i) {
    return Card(this->rank - i, this->suit, "assets/imgs/card_back.png");
}

bool Card::operator==(const Card& c) {
    
    if ((this->rank == c.rank) && (this->suit == c.suit))
        return true;

    return false;

}

bool Card::operator!=(const Card& c) {
    
    if (*this == c)
        return false;

    return true;

}

void Card::loadImage() {
    this->cardImage = LoadTextureFromImage(this->img);
}

void Card::displayCard(float x, float y) {
    DrawTexture(this->cardImage, x, y, WHITE);
}