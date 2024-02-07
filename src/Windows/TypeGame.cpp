#include "TypeGame.h"


TypeGame::TypeGame(){
	Game = "classic";
	FigColor.push_back(sf::Color(255, 250, 250));
	FigColor.push_back(sf::Color(28, 28, 28));

	ColorMoves = sf::Color(0, 255, 0,51);
	ColorEnemMoves = sf::Color(255, 0, 0);
	ColorFrendMoves = sf::Color(0, 255, 255);

	Type();
}

void TypeGame::CreateAll(){
	float PosTGB = 13;
	GameBoxs.clear();
	TGBackground = CreateButton(Perc(60,WinSizeX),Perc(60,WinSizeY), Perc(PosTGB, WinSizeX), Perc(PosTGB, WinSizeY),
		sf::Color(119, 136, 153,50),sf::Color(0,0,0));
	for (int i = 0, j = 0; i < 16;  i++) {
		sf::RectangleShape Sq = CreateButton(Perc(10, WinSizeX), Perc(10, WinSizeY), Perc((PosTGB + 2) * ((i % 4) + 1), WinSizeX),
											 Perc((PosTGB + 2) * ((i/4) + 1), WinSizeY), sf::Color(119, 136, 153, 50), sf::Color(0, 0, 0));
		GameBoxs.push_back(Sq);
	}
}

void TypeGame::WinAll(sf::RenderWindow& win){
	win.draw(TGBackground);
	for (auto box : GameBoxs)
		win.draw(box);
}

int TypeGame::getQuantFigure(){
	return QuantFigure;
}

std::string TypeGame::getGame(){
	return Game;
}

int TypeGame::getSizeBoard(std::string TypeSis) {
	if (TypeSis == "X" || TypeSis == "x")
		return SizeBoardX;
	else if (TypeSis == "Y" || TypeSis == "y")
		return SizeBoardY;
}

sf::Color TypeGame::getColorMoves() {
	return ColorMoves;
}

sf::Color TypeGame::getColorEnemMoves() {
	return ColorEnemMoves;
}

sf::Color TypeGame::getColorFrendMoves() {
	return ColorFrendMoves;
}

void TypeGame::DownTx(std::vector<sf::Texture>& Textures, std::string NameFigure) {
	if (NameFigure == "King") {
		King.TxFigure.clear();
		for (auto Textur : Textures)
			King.TxFigure.push_back(Textur);
	} else if (NameFigure == "Queen") {
		Queen.TxFigure.clear();
		for (auto Textur : Textures)
			Queen.TxFigure.push_back(Textur);
	} else if (NameFigure == "Rook") {
		Rook.TxFigure.clear();
		for (auto Textur : Textures)
			Rook.TxFigure.push_back(Textur);
	} else if (NameFigure == "Bishop") {
		Bishop.TxFigure.clear();
		for (auto Textur : Textures)
			Bishop.TxFigure.push_back(Textur);
	} else if (NameFigure == "Knight") {
		Knight.TxFigure.clear();
		for (auto Textur : Textures)
			Knight.TxFigure.push_back(Textur);
	} else if (NameFigure == "Pawn") {
		Pawn.TxFigure.clear();
		for (auto Textur : Textures)
			Pawn.TxFigure.push_back(Textur);
	}

}

void TypeGame::Type() {
	if (Game == "classic") {
		QuantFigure = 0;
		QuantPlayer = 2;
		King.Quantity = 1;
		Queen.Quantity = 1;
		Rook.Quantity = 2;
		Bishop.Quantity = 2;
		Knight.Quantity = 2;
		Pawn.Quantity = 8;
		QuantFigure = King.Quantity + Queen.Quantity + Rook.Quantity + 
			Bishop.Quantity + Knight.Quantity + Pawn.Quantity;
		SizeBoardX = 8; SizeBoardY = 8;
	}
}