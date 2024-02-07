#include "Figure.h"

Figure::Figure(){
	SizeSquare = Perc(7.05, WinSizeY);
	StartPosX = Perc(9.25, WinSizeX); StartPosY = Perc(14.95, WinSizeY); // for left up angle 
	Press = false;

}

sf::RectangleShape Figure::CreateFigure(int x, int y, const sf::Texture& Texter,sf::Color color) {
	sf::RectangleShape fig;
	fig = CreateButton(SizeSquare, SizeSquare,
		StartPosX + SizeSquare * x, StartPosY + SizeSquare * y,
		color, sf::Color(255, 0, 0, 0));
	if (Texter.getSize() != sf::Vector2u(0, 0))
		fig.setTexture(&Texter);
	return fig;
}

void Figure::WinFigure(sf::RenderWindow& win){
	win.draw(figure);
}

void Figure::WinMove(sf::RenderWindow& win) {

	for (auto Move : MoversCircle)
		win.draw(Move);

	for (auto Move : MoversSquare)
		win.draw(Move);
}

void Figure::setFigure(sf::RectangleShape Newfigure){
	figure = Newfigure;
}

void Figure::setTypeFigure(std::string NewTypeFigure){
	TypeFigure = NewTypeFigure;
}

void Figure::setPlayer(std::string NewPlayer){
	Player = NewPlayer;
}

void Figure::setColor(std::string NewColor) {
	Color = NewColor;
}

void Figure::setStartPos(std::string NewStartPos) {
	StartPos = NewStartPos;
}

void Figure::setTypeGame(std::string NewTypeGame) {
	TypeGame = NewTypeGame;
}

void Figure::setPress(bool NewPress) {
	Press = NewPress;
}

sf::RectangleShape& Figure::getFigureRef(){
	return figure;
}

std::string Figure::getPlayer(){
	return Player;
}

std::string Figure::getStartPos() {
	return StartPos;
}

float Figure::getPosY(int y){
	return StartPosX + SizeSquare * (y - 1);
}


std::string Figure::getTypeFigure() {
	return TypeFigure;
}

sf::RectangleShape Figure::getFigure(){
	return figure;
}

bool Figure::getPress() {
	return Press;
}

int Figure::getPosFig(std::string  TypeSis) {
	if (TypeSis == "X" || TypeSis == "x") {
		return 	round((figure.getPosition().x - StartPosX) / SizeSquare);
	}
	else if (TypeSis == "Y" || TypeSis == "y") {
		return 	round((figure.getPosition().y - StartPosY) / SizeSquare);
	}
}
