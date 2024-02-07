#pragma once

#include <iostream>
#include <string>
#include <vector>


#include <SFML/Graphics.hpp>

#include "../Logic.h"

#define Perc(x,y) (((x)*(y))/100)

class Figure : public Logic {
private:    
    bool Press;
    float SizeSquare;
    float StartPosX, StartPosY;//Precent pos [0][0]

    std::string Player;
    std::string StartPos;
    std::string Color = "";
    std::string TypeFigure = "";
    std::string TypeGame = "";

    sf::RectangleShape figure;  
protected:
public:
    std::vector<sf::RectangleShape> MoversSquare;
    std::vector<sf::CircleShape> MoversCircle;
    Figure();

    //sf::RectangleShape CreateFigure(int x, int y, sf::Texture&, sf::Color);
    sf::RectangleShape CreateFigure(int x, int y, const  sf::Texture& Texter = sf::Texture(), sf::Color color = sf::Color::White);
    void WinFigure(sf::RenderWindow&);
    void WinMove(sf::RenderWindow&);
    
    //set
    void setFigure(sf::RectangleShape);
    void setTypeFigure(std::string);
    void setPlayer(std::string);
    void setColor(std::string);
    void setStartPos(std::string);
    void setTypeGame(std::string);
    void setPress(bool);

    //get
    sf::RectangleShape & getFigureRef();
    sf::RectangleShape getFigure();

    std::string getPlayer();
    std::string getStartPos();
    std::string getTypeFigure();

    float getPosY(int);

    bool getPress();
    
    int getPosFig(std::string);
};

