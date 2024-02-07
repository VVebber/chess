#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../Logic.h"

#define Perc(x,y) (((x)*(y))/100)

class MainMenu : public Logic {
private:
protected:
    bool PresAndHor;

    float SizeBtnX, SizeBtnY;                            //button size by Y

    std::vector<sf::RectangleShape> Buttons;  //Buttons vector
    std::vector<sf::Texture> Textures;        //Texture vector
    std::vector<sf::Text> Texts;              //Texts vector



    int QuanBtn;                             //number of buttons
public:
    MainMenu();
    MainMenu(std::vector<sf::Texture>, int, std::vector<sf::Font>);
   
    void CreateAll() ;
    void WinButton(sf::RenderWindow&);

    void hover();
    
    template<class T1, class T2, class T3>
    void PresMainMenu(sf::RenderWindow& win, T1& PlayMenu, T2& typeGame,
        std::vector<T3>& figures);

    void SizeBtn(float,float);
    //Create button(block and txt)

    //set
    void setPresAndHor(bool);
    //get
    bool getPresAndHor();

};


template<class T1, class T2, class T3>
void MainMenu::PresMainMenu(sf::RenderWindow& win, T1& PlayMenu, T2& typeGame,
                            std::vector<T3>& figures) {
    if (Buttons.size() != 0) {
        if (Buttons[0].getGlobalBounds().contains(MousePosPres)) {//Играть
            PresAndHor = false;
            typeGame.CreateFigures(figures);
            PlayMenu.setPresAndHor(true);
            PlayMenu.CreateAll();
            Buttons.clear();
            Texts.clear();
        }
        else if (Buttons[2].getGlobalBounds().contains(MousePosPres))//выход
            win.close();
    }
    //delete X and Y mouse
    MousePosPres.x = -1; MousePosPres.y = -1;
}
