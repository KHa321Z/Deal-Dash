#include "pile.h"

Pile::Pile(Image& img, float x, float y) : Deck(img, x, y), offSet(30) {
    this->sound = LoadSound("assets/sound/flip.wav");
}

void Pile::showTop(bool deck) {

    if (top() != 0 && top()->isHidden() && deck)
        top()->showCard(), PlaySound(this->sound);
        
    else if (top() != 0 && top()->isHidden())
        top()->showCard();

}

bool Pile::suitSelect() {

    bool started = false;

    for (int i = 0; i < this->getSize() - 1; i++) {

        if ((*this)[i]->getRank() == 13)
            started = true;
        
        if ((*this)[i]->getRank() != ((*this)[i + 1]->getRank() + 1))
            started = false;
        
        else if ((*this)[i + 1]->getRank() == 1 && started) 
            return true;
        
    }

    return false;

}

bool Pile::suitSelect(int index) {

    bool started = true;

    for (int i = index; i < this->getSize() - 1; i++) {
        
        if ((*this)[i]->getRank() != ((*this)[i + 1]->getRank() + 1))
            started = false;
    }

    return started;

}

void Pile::display() {

    if (this->empty())
        this->drawEmpty();

    else
        for (int i = 0; i < this->getSize(); i++)
            if ((*this)[i]->isHidden())
                DrawTexture(this->img, this->position.x, this->position.y + offSet * i, WHITE);
            else
                (*this)[i]->displayCard(this->position.x, this->position.y + offSet * i);

}

bool Pile::isHovering() {
    return ((GetMouseX() >= this->position.x) && (GetMouseX() <= this->position.x + this->width) && (GetMouseY() >= this->position.y) && (GetMouseY() <= this->position.y + this->height + this->offSet * this->getSize()));
}

int Pile::isClicked() {
    
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && this->isHovering()) {

        int index = (GetMouseY() - this->position.y) / this->offSet;

        if (index >= this->getSize() - 1)
            return 1;

        else if (this->suitSelect(index))
            return (this->getSize() - index);

        else
            return 0;

    }

    return 0;
    
}

bool Pile::isDropped() {
    return (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && this->isHovering());
}