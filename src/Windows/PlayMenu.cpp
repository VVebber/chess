#include "PlayMenu.h"

PlayMenu::PlayMenu(std::vector<sf::Texture> NewTexture, int NewQuanBtn, std::vector<sf::Font> NewFont, std::vector<sf::Texture> NewTxChessBoard) 
	: MainMenu(NewTexture, NewQuanBtn, NewFont) {
    for (auto Textur : NewTxChessBoard)
        TxChessBoard.push_back(Textur);
    FigureGo = -1;

}

void PlayMenu::CreateAll(){
    Buttons.clear(); Texts.clear();
    //
    SizeBtn(26, 8);
    //Create color for buttons
    sf::Color ColorBtn(sf::Color(139, 69, 19));
    sf::Color ColorLine(sf::Color(245, 245, 220));
    /*Create buttons
    * QuanBtn - Quantiti Button
    */
    float PrecX = 7, PrecY = 12;
    float SizeChess = Perc(62.5, WinSizeY);
    ///Create CHESSBOARD
    ChessBoard = CreateButton(SizeChess, SizeChess, 
                              Perc(PrecX, WinSizeX), Perc(PrecY, WinSizeY),
                              sf::Color::White, sf::Color::White);
    ChessBoard.setTexture(&TxChessBoard[0]);

    PrecX = 75; PrecY = 12;

    for (int i = 0; i < QuanBtn; i++) {
        sf::RectangleShape Button = CreateButton(SizeBtnX, SizeBtnY,
            Perc(PrecX, WinSizeX) - SizeBtnX / 2, Perc(PrecY, WinSizeY) + ((SizeBtnY + Perc(2, WinSizeY)) * i),
            ColorBtn, ColorLine);
        Buttons.push_back(Button);
    }

    for (int i = 0; i < Buttons.size(); i++) {
        std::string Word;

        switch (i) {
        case 0:
            Word = "Start white";
            break;
        case 1:
            Word = "Start black";
            break;
        case 2:
            Word = "Board type";
            break;
        case 3:
            Word = "Education";
            break;
        case 4:
            Word = "back";
            break;

        }
        sf::Text text = CreatTxtBtn(Perc(PrecX + 1, WinSizeX) - SizeBtnX / 2, Perc(PrecY + 1, WinSizeY) + ((SizeBtnY + Perc(2, WinSizeY)) * i),
            SizeBtnY, Word, sf::Color::Blue);
        Texts.push_back(text);

    }
}

void PlayMenu::WinButton(sf::RenderWindow &win){
    win.draw(ChessBoard);
    for (auto& button : Buttons) {
        win.draw(button);
    }

    for (auto& text : Texts) {
        win.draw(text);
    }
}

//dont work (work, but ...)
bool PlayMenu::MoveInBoard(sf::RectangleShape Move){
    if (ChessBoard.getGlobalBounds().contains(Move.getPosition())) {
        return false;
    } else {
        return true;
    }
}

void PlayMenu::setFigureGo(int NewFigureGo){
    FigureGo = NewFigureGo;
}

int PlayMenu::getFigureGo(){
    return FigureGo;
}

