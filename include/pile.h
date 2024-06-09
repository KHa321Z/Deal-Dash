#pragma once
#include "deck.h"

class Pile : public Deck {

    int offSet;

    public:

        Pile(Image&, float, float);

        void showTop(bool = true);

        bool suitSelect();
        bool suitSelect(int);

        bool suitcompleted(){// for classic

            bool started = false;

            for (int i = 0; i < this->getSize() - 1; i++) {

                if ((*this)[i]->getRank() == 13)
                    started=true;
                
                if ((*this)[i]->getRank()!=((*this)[i + 1]->getRank()+1)){
                    if((((*this)[i]->getSuit()==HEARTS||(*this)[i]->getSuit()==DIAMONDS)&&((*this)[i + 1]->getSuit()==HEARTS||(*this)[i + 1]->getSuit()==DIAMONDS))||(((*this)[i]->getSuit()==SPADES||(*this)[i]->getSuit()==CLUBS)&&((*this)[i + 1]->getSuit()==SPADES||(*this)[i + 1]->getSuit()==CLUBS)))
                    started=false;
                }

                else if((*this)[i + 1]->getRank()==1&&started==true)
                    return true;
                
            }

            return false;
        }

        virtual void display() override;

        virtual bool isHovering() override;
        virtual int isClicked() override;
        bool isDropped();

};