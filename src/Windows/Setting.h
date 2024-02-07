#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "MainMenu.h"
class Setting : public MainMenu{
private:
	std::vector<sf::Texture> TxBackground;

	sf::RectangleShape Background;

	std::string TypeDevise;

protected:
public:
	Setting(std::vector<sf::Texture>, int, std::vector<sf::Font>, std::vector<sf::Texture>,  std::string);

	void CreateAll();

	sf::RectangleShape getBackground() const;

};

