#include <iostream>
#include <vector>
#include "deck.h"
#include "card.h"

Deck::Deck(Image& img, float x, float y) : RectangularButton(img, Vector2{ x, y }, CARD_WIDTH, CARD_HEIGHT), loadedResources(0) {

    UnloadSound(this->sound);
    this->sound = LoadSound("assets/sound/shuffle.wav");

}

Deck::~Deck() {

    UnloadSound(this->sound);

    while (!this->empty())
        delete this->pop();

}

Card* Deck::operator[] (int i) {
    return cards.at(i);
}

int Deck::getSize() {
    return cards.size();
}

Card* Deck::top() {
    return (this->getSize() ? cards.back() : 0);
}

bool Deck::push(Card* card) {

    cards.push_back(card);
    return true;

}

Card* Deck::pop() {

    Card* c = cards.back();
    cards.pop_back();

    return c;

}

void Deck::initialize(bool standard) {

    if (standard)
        for (int i = (int)Suit::SPADES; i < Suit::DIAMONDS; i++)
            for (int j = 1; j <= 13; j++) 
                this->push(new Card(j, Suit(i), ("assets/imgs/" + std::to_string(i) + "_" + std::to_string(j) + ".png").c_str()));

    else {

        std::promise<int> loadingPromise;
        this->loadingFuture = loadingPromise.get_future();

        std::thread loadingThread([this]() mutable {

            for (int i = 0; i < 8; i++)
                for (int j = 1; j <= 13; j++) 
                    this->push(new Card(j, Suit(1), ("assets/imgs/1_" + std::to_string(j) + ".png").c_str())),
                    loadedResources++;

        });

        loadingThread.detach();

    }

}

void Deck::shuffle() {

    int size = this->getSize();
    std::vector<Card *> c;

    for (int i = 0; i < size; i++) {

        int index = rand() % (size - i);

        c.push_back(cards.at(index));
        cards.erase(cards.begin() + index);

    }
    
    cards = c;

}

bool Deck::empty() {
    return cards.empty();
}

void Deck::drawEmpty() {
    DrawRectangleRoundedLines(Rectangle{ this->position.x, this->position.y, this->width, this->height }, 0.05, 10, 2, Color{ 35, 87, 62, 255 });
}

void Deck::display() {

    if (this->empty())
        this->drawEmpty();
    else
        this->RectangularButton::display();

}

int Deck::getLoadedResources() {
    if (loadingFuture.valid()) {
        return loadingFuture.get();
    } else {
        return 0;
    }
}