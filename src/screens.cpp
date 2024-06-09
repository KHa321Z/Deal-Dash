#include <iostream>
#include "screens.h"

HomeScreen::HomeScreen(float w, float h) : Screen(w, h, 1) {

    this->title = LoadTexture((this->imgPath + "title.png").c_str());

    Image play = LoadImage((this->imgPath + "play.png").c_str());
    Image settings = LoadImage((this->imgPath + "settings.png").c_str());
    Image user = LoadImage((this->imgPath + "user.png").c_str());

    ImageResize(&play, 300, 300);
    ImageResize(&settings, 200, 200);
    ImageResize(&user, 200, 200);

    this->playButton = new CircularButton(play, Vector2{ width / 2, height * 2 / 3 }, play.width / 2);
    this->settingsButton = new CircularButton(settings, Vector2{ width / 2 - play.width - 100, height * 2 / 3 }, settings.width / 2);
    this->userButton = new CircularButton(user, Vector2{ width / 2 + play.width + 100, height * 2 / 3 }, user.width / 2);

    UnloadImage(play);
    UnloadImage(settings);
    UnloadImage(user);

}

HomeScreen::~HomeScreen() {

    delete this->playButton;
    delete this->settingsButton;
    delete this->userButton;

}

void HomeScreen::Draw() {

    this->Screen::Draw();

    DrawTexture(this->title, 0, 150, WHITE);

    this->playButton->display();
    this->settingsButton->display();
    this->userButton->display();

}

int HomeScreen::eventListener() {

    if (this->playButton->isClicked())
        return 2;

    else if (this->settingsButton->isClicked());

    else if (this->userButton->isClicked());

    else if (this->playButton->isHovering() || this->settingsButton->isHovering() || this->userButton->isHovering())
        return -1;

    return 0;

}



SelectScreen::SelectScreen(float w, float h) : Screen(w, h, 1), loadingFont(LoadFontEx("assets/fonts/Intro.ttf", 100, NULL, 0)), loadingText("LOADING...") {

    this->title = LoadTexture("assets/imgs/title.png");

    Image spider = LoadImage("assets/imgs/spider.png");
    Image classic = LoadImage("assets/imgs/classic.png");
    Image home = LoadImage("assets/imgs/home.png");

    ImageResize(&spider, 400, 575);
    ImageResize(&classic, 400, 575);
    ImageResize(&home, 150, 150);

    this->spiderButton = new RectangularButton(spider, Vector2{ width / 2 - 150 - spider.width, height * 35 / 100 }, spider.width, spider.height);
    this->classicButton = new RectangularButton(classic, Vector2{ width / 2 + 150, height * 35 / 100 }, classic.width, classic.height);
    this->homeButton = new CircularButton(home, Vector2{ width - 150, height - 150 }, home.width / 2);

    UnloadImage(spider);
    UnloadImage(classic);
    UnloadImage(home);

}

SelectScreen::~SelectScreen() {

    UnloadFont(this->loadingFont);

    if (this->spiderButton)
        delete this->spiderButton;
    
    if (this->classicButton)
        delete this->classicButton;

    delete this->homeButton;

}

void SelectScreen::Draw() {

    this->Screen::Draw();

    DrawTexture(this->title, 0, 50, WHITE);

    this->homeButton->display();

    if (this->spiderButton && this->classicButton)
        this->spiderButton->display(), 
        this->classicButton->display();

}

void SelectScreen::DrawLoading(int loadedResources) {

    DrawTextEx(this->loadingFont, this->loadingText, Vector2{ 775, 450 }, 75, 1, BLACK);

    DrawRectangleRoundedLines(Rectangle{ 520, 560, 920, 130 }, 0.35, 15, 12, BLACK);

    for (int i = 0; i < (loadedResources / 104.0 * 10); i++)
        DrawRectangleRounded(Rectangle{ float(535 + (i * 90)), 575, 80, 100 }, 0.35, 12, BLACK);

    //DrawText((std::to_string(loadedResources / 104.0 * 100) + "%").c_str(), 450, 550, 50, BLACK);

}

int SelectScreen::eventListener() {

    if (this->spiderButton && this->spiderButton->isClicked()) 
        return 3;

    else if (this->classicButton && this->classicButton->isClicked())
        return 4;

    else if (this->homeButton->isClicked())
        return 1;

    else if (this->homeButton->isHovering() || (this->classicButton && this->classicButton->isHovering()) || (this->spiderButton && this->spiderButton->isHovering()))
        return -1;

    return 0;

}



SpiderScreen::SpiderScreen(float w, float h) : Screen(w, h, 0), win(0), winSound(LoadSound("assets/sound/win.wav")), invalidSound(LoadSound("assets/sound/invalid.wav")), scoreFont(LoadFontEx("assets/fonts/frontage.ttf", 100, NULL, 0)), score("SCORE"), scoreValue(500), previousPile(0) {

    Image home = LoadImage("assets/imgs/home.png");
    Image settings = LoadImage("assets/imgs/settings.png");
    Image cardBack = LoadImage("assets/imgs/card_back.png");

    ImageResize(&home, 100, 100);
    ImageResize(&settings, 100, 100);
    ImageResize(&cardBack, CARD_WIDTH, CARD_HEIGHT);

    this->homeButton = new CircularButton(home, Vector2{  75, 75 }, home.width / 2);
    this->settingsButton = new CircularButton(settings, Vector2{ 200, 75 }, settings.width / 2);
    this->deck = new Deck(cardBack, this->width - 2 * CARD_WIDTH, this->height - CARD_HEIGHT - 50);

    for (int i = 0; i < 10; i++)
        this->piles.push_back(new Pile(cardBack, 75 + i * 180, 200));

    UnloadImage(home);
    UnloadImage(settings);
    UnloadImage(cardBack);

    this->deck->initialize(0);

}

SpiderScreen::~SpiderScreen() {

    UnloadFont(this->scoreFont);
    UnloadTexture(this->winImage);
    UnloadSound(this->winSound);
    UnloadSound(this->invalidSound);

    delete this->homeButton;
    delete this->settingsButton;
    delete this->deck;

    for (int i = 0; i < 10; i++)
        delete this->piles.at(i);

}

void SpiderScreen::GameStart() {

    this->deck->shuffle();

    int size = this->deck->getSize();

    for (int i = 0; i < size; i++)
        (*this->deck)[i]->loadImage();

    for (int i = 0; i < size - 40; i++)
        this->piles.at(i % 10)->push(this->deck->pop());

    for (int i = 0; i < 10; i++)
        this->piles.at(i)->showTop();

}

void SpiderScreen::Draw() {

    this->Screen::Draw();

    DrawTextEx(this->scoreFont, this->score, Vector2{ 550, 40 }, 100, 0.1f, BLACK);
    DrawTextEx(this->scoreFont, std::to_string(this->scoreValue).c_str(), Vector2{ 1150, 40 }, 100, 0.1f, BLACK);

    this->homeButton->display();
    this->settingsButton->display();
    this->deck->display();

    if (this->win)
        DrawTexture(this->winImage, 650, 400, WHITE);

    for (int i = 0; i < 10; i++)
        this->piles.at(i)->display();

    for (int i = 0; i < this->selectedCards.size(); i++)
        // need to remember the coords relative to the card when mouse was pressed
        this->selectedCards.at(this->selectedCards.size() - i - 1)->displayCard(GetMouseX(), GetMouseY() + i * 30);

}

int SpiderScreen::eventListener() {

    if (this->homeButton->isClicked())
        return 1;

    else if (this->settingsButton->isClicked());

    else if (this->deck->isHovering() && this->deck->empty())
        return -2;

    else if (this->deck->isClicked()) {

        this->scoreValue--;

        for (int i = 0; i < 10; i++) {

            this->piles.at(i)->push(this->deck->pop());
            this->piles.at(i)->showTop(0);

            if (this->piles.at(i)->suitSelect()) {

                for (int j = 0; j < 13; j++)
                    this->piles.at(i)->pop();

                this->piles.at(i)->showTop();
                this->scoreValue += 101;

            }

        }

    }

    else if (this->homeButton->isHovering() || this->settingsButton->isHovering() || this->deck->isHovering())
        return -1;

    for (int i = 0; i < 10; i++) {

        if (this->selectedCards.size() == 0) {

            int index = this->piles.at(i)->isClicked();

            if (index) {

                this->previousPile = this->piles.at(i);

                for (int j = 0; j < index; j++)
                    this->selectedCards.push_back(this->piles.at(i)->pop());

            }

        } else if (this->piles.at(i)->isDropped()) {

            if (!this->piles.at(i)->top() || (*(this->piles.at(i)->top()) - 1 == *(this->selectedCards.back()))) {

                if (this->previousPile != this->piles.at(i))
                    this->scoreValue--;

                this->previousPile->showTop();
                this->previousPile = 0;
                
                while (!this->selectedCards.empty())
                    this->piles.at(i)->push(this->selectedCards.back()), 
                    this->selectedCards.pop_back();

                if (this->piles.at(i)->suitSelect()) {

                    for (int j = 0; j < 13; j++)
                        this->piles.at(i)->pop();

                    this->piles.at(i)->showTop();
                    this->scoreValue += 101;

                    bool checkWin = true;

                    for (int j = 0; j < 10; j++)
                        if (!this->piles.at(j)->empty())
                            checkWin = false, j = 10;
                    
                    if (checkWin) {
                        
                        PlaySound(this->winSound);
                        Image img = LoadImage("assets/imgs/win.png");
                        ImageResize(&img, 630, 500);

                        this->win = true;
                        this->winImage = LoadTextureFromImage(img);

                        UnloadImage(img);

                    }

                }
                
            } else {

                PlaySound(this->invalidSound);

                while (!this->selectedCards.empty())
                    this->previousPile->push(this->selectedCards.back()), 
                    this->selectedCards.pop_back();

                this->previousPile = 0;

            }

        }

    }

    return 0;

}