#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "body.hpp"

class ball : public body{
public:

	sf::CircleShape cirkel;

	ball(sf::Vector2f position,
		float size = 30.0,
		sf::Color color = sf::Color::Red);

	void draw( sf::RenderWindow & window ) const;

	void move( sf::Vector2f delta );

	void jump( sf::Vector2f target );
	void jump( sf::Vector2i target );

	sf::FloatRect getFloatRect() {
		return globalBounds;
	}

	sf::Vector2f getPosition() {
		return position;
	}

private:
	sf::Vector2f position;
	float size;
	sf::Color color;

	sf::FloatRect globalBounds;
};

#endif
