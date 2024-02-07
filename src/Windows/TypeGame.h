#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "MainMenu.h"

#include <SFML/Graphics.hpp>

#define Perc(x,y) (((x)*(y))/100)

struct FigInTG{
	int Quantity;
	std::vector<sf::Texture> TxFigure;
};


class TypeGame : public MainMenu{
private:
	FigInTG King;
	FigInTG Queen;
	FigInTG Rook;
	FigInTG Bishop;
	FigInTG Knight;
	FigInTG Pawn;

	int QuantPlayer;
	int QuantFigure;

	int SizeBoardX, SizeBoardY;
	std::string Game;

	std::vector<sf::RectangleShape> GameBoxs;
	std::vector<sf::Color> FigColor;

	sf::Color ColorMoves;
	sf::Color ColorEnemMoves;
	sf::Color ColorFrendMoves;

	
protected:
	sf::RectangleShape TGBackground;
	sf::RectangleShape Close;

public:
	TypeGame();

	void CreateAll();
	void WinAll(sf::RenderWindow&);
	void DownTx(std::vector<sf::Texture>&, std::string);
	
	template<class T1>
	void PressedTypeGame(T1&);


	template <class T1>
	void CreateFigures(std::vector<T1>& figures);
	void Type();
	//set

	//get
	sf::Color getColorMoves();
	sf::Color getColorEnemMoves();
	sf::Color getColorFrendMoves();

	std::string getGame();
	
	int getQuantFigure();
	int getSizeBoard(std::string);
};




template<class T1>
inline void TypeGame::PressedTypeGame(T1& PlayMenu){
	if (TGBackground.getGlobalBounds().contains(MousePosPres)) {
		std::cout<<"eror";
	}
	else if (!TGBackground.getGlobalBounds().contains(MousePosPres)) {
		PresAndHor = false;
		TGBackground = DeleteShape();
		GameBoxs.clear();
		PlayMenu.setPresAndHor(true);
		PlayMenu.CreateAll();
	}
	MousePosPres.x = 0; MousePosPres.y = 0;
}

template <class T1>
void TypeGame::CreateFigures(std::vector<T1>& figures) {
	for (int j = 0; j < QuantPlayer; j++) {
		T1 fig;
		for (int i = 0; i < King.Quantity; i++) {
			fig.setFigure(fig.CreateFigure(3,(j == 0? 0: 7), King.TxFigure[0], FigColor[j]));
			fig.setPlayer("Player_" + std::to_string(j));
			fig.setTypeFigure("King");
			figures.push_back(fig);
		}
		for (int i = 0; i < Queen.Quantity; i++) {
			fig.setFigure(fig.CreateFigure(4, (j == 0 ? 0 : 7), Queen.TxFigure[0], FigColor[j]));
			fig.setPlayer("Player_" + std::to_string(j));
			fig.setTypeFigure("Queen");
			figures.push_back(fig);
		}
		for (int i = 0; i < Rook.Quantity; i++) {
			fig.setFigure(fig.CreateFigure((i == 0? 0: 7), (j == 0 ? 0 : 7), Rook.TxFigure[0], FigColor[j]));
			fig.setPlayer("Player_" + std::to_string(j));
			fig.setTypeFigure("Rook");
			figures.push_back(fig);
		}
		for (int i = 0; i < Bishop.Quantity; i++) {
			fig.setFigure(fig.CreateFigure((i == 0 ? 2 : 5), (j == 0 ? 0 : 7), Bishop.TxFigure[0], FigColor[j]));
			fig.setPlayer("Player_" + std::to_string(j));
			fig.setTypeFigure("Bishop");
			figures.push_back(fig);
		}
		for (int i = 0; i < Knight.Quantity; i++) {
			fig.setFigure(fig.CreateFigure((i == 0 ? 1 : 6), (j == 0 ? 0 : 7), Knight.TxFigure[0], FigColor[j]));
			fig.setPlayer("Player_" + std::to_string(j));
			fig.setTypeFigure("Knight");
			figures.push_back(fig);
		}
		for (int i = 0; i < Pawn.Quantity; i++) {
			fig.setFigure(fig.CreateFigure(i, (j == 0 ? 1 : 6), Pawn.TxFigure[0], FigColor[j]));
			fig.setPlayer("Player_" + std::to_string(j));
			fig.setTypeFigure("Pawn");
			figures.push_back(fig);
		}
	}
}
