#include <SFML/Graphics.hpp>
#include "square.hpp"

square::square(sf::Vector2f size, sf::Vector2f position, sf::Color color):
	size{size},
	position{position},
	color{color}
{
	rectangle.setPosition(position);
	rectangle.setSize(size);
	rectangle.setFillColor(color);
}

void square::draw(sf::RenderWindow & window) const {
	window.draw(rectangle);
}

void square::move(sf::Vector2f delta) {
	position += delta;
	rectangle.setPosition(position);
}

void square::jump(sf::Vector2f target) {
	position = target;
	rectangle.setPosition(position);
}

void square::jump(sf::Vector2i target) {
	jump(sf::Vector2f(
		static_cast< float >(target.x),
		static_cast< float >(target.y)
	));
}
