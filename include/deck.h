#pragma once
#include <vector>
#include <future>
#include <thread>
#include "raylib.h"
#include "card.h"
#include "button.h"

class Deck : public RectangularButton {
       
    std::vector<Card*> cards;

    public:

        Deck(Image&, float, float);
        virtual ~Deck();

        int getSize();

        Card* operator[](int);

        Card* top();
        bool push(Card* card);
        Card* pop();

        virtual void initialize(bool standard = true);
        void shuffle();
        bool empty();

        virtual void drawEmpty();
        virtual void display() override;

        std::atomic<int> loadedResources;
        std::future<int> loadingFuture;
        int getLoadedResources();

};