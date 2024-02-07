#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "MainMenu.h"

#include "../Functions.h"

#define Perc(x,y) (((x)*(y))/100)

class PlayMenu : public MainMenu {
private:
    int FigureGo;

    std::string TupeChess;
    std::vector<sf::Texture> TxChessBoard;
    sf::RectangleShape ChessBoard;

protected:
public:
    PlayMenu(std::vector<sf::Texture>, int, std::vector<sf::Font>, std::vector<sf::Texture>);

    void CreateAll();
    void WinButton(sf::RenderWindow&);

    template<class T1, class T2, class T3>
    void PressedPlayMenu(std::vector<T1>&,T2&,T3&);

    bool MoveInBoard(sf::RectangleShape);
    //set
    void setFigureGo(int);

    //get
    int getFigureGo();

};

template<class T1, class T2, class T3>
void PlayMenu::PressedPlayMenu(std::vector<T1>& figures, T2& mainMenu, T3& typeGame) {
    if (Buttons.size() != 0) {
        if (Buttons[0].getGlobalBounds().contains(MousePosPres)) {
            PresAndHor = false;
            ChessBoard.setTexture(&TxChessBoard[1]);
            RS::swap_Pos(figures[0].getFigureRef(), figures[1].getFigureRef());
            RS::swap_Pos(figures[16].getFigureRef(), figures[17].getFigureRef());

            for (int i = 0; i < figures.size(); i++) {
                figures[i].MoversSquare.clear();
                figures[i].setTypeGame(typeGame.getGame());
                if (figures[i].getPlayer() == "Player_0") {//Player_1
                    figures[i].setColor("White");
                    figures[i].setStartPos("Up");
                } else if (figures[i].getPlayer() == "Player_1") {//Player_2
                    figures[i].setColor("Black");
                    figures[i].setStartPos("Down");
                }
            }

            for (int i = 0; i < typeGame.getQuantFigure(); i++) {
                RS::swap_Pos(figures[i].getFigureRef(), figures[i + typeGame.getQuantFigure()].getFigureRef());
            }
            
            Buttons.clear();
            Texts.clear();
        }
        else if (Buttons[1].getGlobalBounds().contains(MousePosPres)) {
            PresAndHor = false;
            ChessBoard.setTexture(&TxChessBoard[0]);

            for (int i = 0; i < figures.size(); i++) {
                figures[i].MoversSquare.clear();
                figures[i].setTypeGame(typeGame.getGame());
                if (figures[i].getPlayer() == "Player_1") {//Player_1
                    figures[i].setColor("Black");
                    figures[i].setStartPos("Down");
                } else if (figures[i].getPlayer() == "Player_0") {//Player_2
                    figures[i].setColor("White");
                    figures[i].setStartPos("Up");
                }
            }

            Buttons.clear();
            Texts.clear();
        }
        else if (Buttons[2].getGlobalBounds().contains(MousePosPres)) {
            PresAndHor = false;
            typeGame.setPresAndHor(true);
            typeGame.CreateAll();
        }
        else if (Buttons[3].getGlobalBounds().contains(MousePosPres)) {
            Texts[3].setString(L"error");
        }
        else if (Buttons[4].getGlobalBounds().contains(MousePosPres)) {
            PresAndHor = false;
            mainMenu.setPresAndHor(true);
            mainMenu.CreateAll();
            ChessBoard = DeleteShape();
            figures.clear();//
            Buttons.clear();
            Texts.clear();
        }
    }
    
}