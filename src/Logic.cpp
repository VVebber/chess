#include "Logic.h"

Logic::Logic() {
    WinSizeX = 1280; WinSizeY = 960;
}


Logic::Logic(std::vector<sf::Font> NewFont = {}){
    for (auto& f : NewFont) {
        font.push_back(f);
    }
}

sf::RectangleShape Logic::CreateButton(float SizeX, float SizeY, float PosX, float PosY, sf::Color ColorBtn, sf::Color ColorLine) {
    sf::RectangleShape Button;
    Button.setSize(sf::Vector2f(SizeX, SizeY));
    Button.setFillColor(ColorBtn);
    Button.setPosition(sf::Vector2f(PosX, PosY));
    Button.setOutlineThickness(1);
    Button.setOutlineColor(ColorLine);
    return Button;
}

sf::Vector2f Logic::getMousePosPres(){
    return MousePosPres;
}

sf::RectangleShape Logic::DeleteShape(){
    sf::RectangleShape delet;
    return delet;
}

sf::Text Logic::CreatTxtBtn(float PosX, float PosY,float SizeTxt, std::string Sting, sf::Color ColorLine) {
    sf::Text TextBtn;
    TextBtn.setFont(font[0]);
    TextBtn.setCharacterSize(SizeTxt - Perc(30, SizeTxt)); //SizeBtnY
    TextBtn.setFillColor(sf::Color(250, 235, 215));
    TextBtn.setPosition(sf::Vector2f(PosX, PosY));
    TextBtn.setOutlineThickness(0.1);
    TextBtn.setOutlineColor(ColorLine);
    TextBtn.setString(sf::String::fromUtf8(Sting.begin(), Sting.end()));
    return TextBtn;
}

void Logic::setEvent(sf::Event NewEvent) {
    event = NewEvent;
}

void Logic::setMousePosPres(sf::Vector2f NewMousePosPres) {
    MousePosPres = NewMousePosPres;
}

void Logic::setMousePosHover(sf::Vector2f NewMousePosHover) {
    MousePosHover = NewMousePosHover;
}

