#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#define Perc(x,y) (((x)*(y))/100)

template <class T1, class T2>
void CreateShapeFull(T1& figure, T2 typeGame);

template <class T1, class T2, class T3>
void GoFigure(std::vector<T1>& figures, T1& figure, T2& playMenu, T3 typeGame);

void Bool(bool& Up, bool& Down, int& sp);





template <class T1, class T2, class T3>
void CustomLogic(sf::RenderWindow& win, std::vector<T1>& figures,T2& typeGame, T3& playMenu) {
	
	if (playMenu.getPresAndHor()) {
		for (auto& figure : figures) {
			if (figure.MoversSquare.size() == 0)
				CreateShapeFull(figure, typeGame);//Moves create
		}
	}
	else if (typeGame.getGame() == "classic") {
		for (auto& figure : figures) {
			if (figure.MoversSquare.size() == 0)
				LogicClassic(figure, figures, typeGame);//Moves create
		}
	}

	if (playMenu.getFigureGo() > 0)
		GoFigure(figures, figures[playMenu.getFigureGo()], playMenu, typeGame);

	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].getFigure().getGlobalBounds().contains(playMenu.getMousePosPres())/* && playMenu.getFigureGo() < 0*/) {
			playMenu.setFigureGo(i);
			break;
		}
	}

	if(figures.size() >= playMenu.getFigureGo())
		figures[playMenu.getFigureGo()].WinMove(win);



	
			
}

template <class T1, class T2, class T3>
void GoFigure(std::vector<T1>& figures, T1& figure, T2& playMenu, T3 typeGame) {

	for (int i = 0; i < figure.MoversSquare.size(); i++) {
		if (figure.MoversSquare[i].getGlobalBounds().contains(playMenu.getMousePosPres())) {
			sf::RectangleShape Newfig = figure.getFigure();
			Newfig.setPosition(figure.MoversSquare[i].getPosition());
			figure.setFigure(Newfig);
		
			
			for (int i2 = 0; i2 < figures.size(); i2++) {
				if (figures[i2].getFigure().getPosition() == Newfig.getPosition() && i2 != playMenu.getFigureGo()) {
					figures.erase(figures.begin() + i2);
					playMenu.setFigureGo(playMenu.getFigureGo() - 1);
				}
				LogicClassic(figures[i2], figures, typeGame);//Moves create
					

			}

			playMenu.setMousePosPres(sf::Vector2f(0,0));
			playMenu.setFigureGo(-1);
			break;
		}
	}
}

template <class T1, class T2>
void CreateShapeFull(T1& figure, T2 typeGame) {
	figure.MoversSquare.clear();

	for (int i = 0; i < typeGame.getSizeBoard("y"); i++) {
		for (int j = 0; j < typeGame.getSizeBoard("x"); j++) {
			sf::RectangleShape Move;
			Move = figure.CreateFigure(i, j,{}, typeGame.getColorMoves());
			if (figure.getFigure().getPosition() == Move.getPosition()) {
				continue;
			}

			figure.MoversSquare.push_back(Move);
		}
	}
}




template <class T1, class T2>
void LogicClassic(T1& figure, std::vector<T1> figures, T2 typeGame) {
	bool Left = true, Right = true, Up = true, Down = true;
	bool LeftUp = true, RightUp = true, LeftDown = true, RightDown = true;

	figure.MoversSquare.clear();


	bool Continue = false;

	if (figure.getTypeFigure() == "Knight")
		return;

	for (int i = 0; i < typeGame.getSizeBoard("y"); i++) {
		sf::RectangleShape Move;
		sf::Vector2f FigPos = figure.getFigure().getPosition();
		if (Down && !(figure.getTypeFigure() == "Pawn" && figure.getStartPos() == "Up")) {
			Move = figure.CreateFigure(figure.getPosFig("x"), figure.getPosFig("y") + (i + 1), {}, typeGame.getColorMoves());
		} else if (Up && !(figure.getTypeFigure() == "Pawn" && figure.getStartPos() == "Down")) {
			Move = figure.CreateFigure(figure.getPosFig("x"), figure.getPosFig("y") - (i + 1), {}, typeGame.getColorMoves());
		}



		for (auto figure : figures) {
			if (figure.getFigure().getPosition() == Move.getPosition()) {
				Bool(Down, Up, i);
				break;
			}
		}

		if (Move.getPosition().y > figure.getPosY(typeGame.getSizeBoard("y") + 1) &&
			Move.getPosition().y < figure.getPosY(1)) {
			Bool(Down, Up, i);
			continue;
		}

		figure.MoversSquare.push_back(Move);

		if (Continue) {
			Continue = false;
			Bool(Down, Up, i);
		}

		if (!Down && !Up) 
			break;
	}
}
//bool Left, bool Right, , bool LeftUp, bool RightUp, bool LeftDown, bool RightDown
 
void Bool(bool& Up, bool& Down, int& sp) {
	sp = -1;
	if (Down) {
		Down = false;
		return;
	}else if (Up) {
		Up = false;
		return;
	}
}
 
// old functions 