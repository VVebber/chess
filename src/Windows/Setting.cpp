#include "Setting.h"

Setting::Setting(std::vector<sf::Texture> NewTexture, int NewQuanBtn, std::vector<sf::Font> NewFont, std::vector<sf::Texture> NewTxBackground,
                std::string NewTypeDevise) : MainMenu(NewTexture, NewQuanBtn, NewFont) {

    TypeDevise = NewTypeDevise;

    for (auto Textur : NewTxBackground)
        TxBackground.push_back(Textur);
}



void Setting::CreateAll(){
    Background = CreateButton(WinSizeX,WinSizeY,0,0);
    Background.setTexture(&TxBackground[0]);
}

sf::RectangleShape Setting::getBackground() const {
    return Background;
}