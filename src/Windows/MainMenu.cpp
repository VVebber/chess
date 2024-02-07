#include "MainMenu.h"

MainMenu::MainMenu() {
    PresAndHor = false;
}

MainMenu::MainMenu(std::vector<sf::Texture> NewTexture = {}, int NewQuanBtn = 0, std::vector<sf::Font> NewFont = {}) : Logic(NewFont){
    for (int i = 0; i < NewTexture.size(); i++)
        Textures[i] = NewTexture[i];

    QuanBtn = NewQuanBtn;
    WinSizeX = 1280; WinSizeY = 960;
    PresAndHor = true;
}

void MainMenu::CreateAll(){
    Buttons.clear(); Texts.clear();
    SizeBtn(26, 8);
    //Create color for buttons
    sf::Color ColorBtn(sf::Color(139, 69, 19));
    sf::Color ColorLine(sf::Color(245, 245, 220));
    /*Create buttons
    * QuanBtn - Quantiti Button
    */
    float PrecX = 50, PrecY = 20;
    for (int i = 0; i < QuanBtn; i++) {
        sf::RectangleShape Button;
        Button = CreateButton(SizeBtnX, SizeBtnY,
            Perc(PrecX, WinSizeX) - SizeBtnX / 2, Perc(PrecY, WinSizeY) + ((SizeBtnY + Perc(2, WinSizeY)) * i),
            ColorBtn, ColorLine);
        Buttons.push_back(Button);
    }
    for (int i = 0; i < Buttons.size(); i++) {
        std::string Word;

        switch (i) {
        case 0:
            Word = "start";
            break;
        case 1:
            Word = "senttings";
            break;
        case 2:
            Word = "exit";
            break;
        }
        sf::Text text;
        text = CreatTxtBtn(Perc(PrecX + 1, WinSizeX) - SizeBtnX / 2, Perc(PrecY + 1, WinSizeY) + ((SizeBtnY + Perc(2, WinSizeY)) * i),
            SizeBtnY, Word, sf::Color::Blue);
        Texts.push_back(text);

    }
}

void MainMenu::WinButton(sf::RenderWindow& win){
    for (auto button : Buttons) {
        win.draw(button);
    }

    for (auto text : Texts) {
        win.draw(text);
    }
}

void MainMenu::hover(){
    for (int i = 0; i < Buttons.size(); i++) {
        if (Buttons[i].getGlobalBounds().contains(MousePosHover)) {
            Buttons[i].setFillColor(sf::Color(160, 82, 45));
            if (i < Texts.size()) {
                Texts[i].setFillColor(sf::Color(0, 0, 0));
            }
        }
        else {
            Buttons[i].setFillColor(sf::Color(139, 69, 19));
            if (i < Texts.size()) {
                Texts[i].setFillColor(sf::Color(255, 248, 220));
            }
        }
    }
}

void MainMenu::SizeBtn(float Percent_X = 25, float Percent_Y = 7) {
    SizeBtnX = (Percent_X * WinSizeX) / 100;
    SizeBtnY = (Percent_Y * WinSizeY) / 100;
}

void MainMenu::setPresAndHor(bool NewPresAndHor){
    PresAndHor = NewPresAndHor;
}

bool MainMenu::getPresAndHor(){
    return PresAndHor;
}
