#ifndef _SQUARE_HPP
#define _SQUARE_HPP

#include <SFML/Graphics.hpp>
#include "body.hpp"

class square: public body{
public:

	sf::RectangleShape rectangle;
	square(sf::Vector2f size, 
		   sf::Vector2f position = sf::Vector2f{ 0,0 },
		   sf::Color color = sf::Color::Blue);

	void draw(sf::RenderWindow & window) const;

	void move(sf::Vector2f delta);

	void jump(sf::Vector2f target);
	void jump(sf::Vector2i target);

	sf::Vector2f getPosition() {
		return position;
	}

private:
	sf::Vector2f size, position;
	sf::Color color;
	sf::FloatRect globalBounds;
};
#endif 
