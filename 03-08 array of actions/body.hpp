#pragma once

#include <SFML/Graphics.hpp>

class body {
public:
	body(){};

	virtual void draw(sf::RenderWindow & window) const = 0;
	virtual void move(sf::Vector2f delta) = 0;
	//virtual void jump(sf::Vector2f target) = 0;
};

