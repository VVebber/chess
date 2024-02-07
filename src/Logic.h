#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#define Perc(x,y) (((x)*(y))/100)

class Logic{
protected:
    std::vector<sf::Font> font;               //font vector

    //for flexibility (maximum size, minimum size)
    int WinSizeX, WinSizeY;

    sf::Event event;                          //Event(click, hover)

    sf::Vector2f MousePosPres;           //mouse click coordinates
    sf::Vector2f MousePosHover;          //mouse hover coordinates


public:
    Logic();
    Logic(std::vector<sf::Font>);
    //functions
    sf::RectangleShape CreateButton(float SizeX, float SizeY, float PosX, float PosY, sf::Color ColorBtn = sf::Color::White, sf::Color ColorLine = sf::Color::White);
    sf::Text CreatTxtBtn(float, float, float, std::string, sf::Color); 
    
    sf::RectangleShape DeleteShape();
    //set

    void setEvent(sf::Event);
    void setMousePosPres(sf::Vector2f);
    void setMousePosHover(sf::Vector2f);

    //get

    sf::Vector2f getMousePosPres();


};

