#pragma once
#include <SFML/Graphics.hpp>

namespace RS {
	inline void swap_Pos(sf::RectangleShape& one, sf::RectangleShape& two) {
		sf::RectangleShape there = one;
		one.setPosition(two.getPosition());
		two.setPosition(there.getPosition());
	}
}