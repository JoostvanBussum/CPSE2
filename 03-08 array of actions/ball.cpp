#include <SFML/Graphics.hpp>
#include "ball.hpp"

ball::ball( sf::Vector2f position, float size, sf::Color color ) :
	position{ position },
	size{ size },
	color{color}
{
	cirkel.setRadius(size);
	cirkel.setPosition(position);
	cirkel.setFillColor(color);
}

void ball::draw( sf::RenderWindow & window ) const {
	window.draw(cirkel);
}

void ball::move( sf::Vector2f delta ){
	position += delta;
	cirkel.setPosition(position);
}

void ball::jump( sf::Vector2f target ){
	position = target;
}

void ball::jump( sf::Vector2i target ){
	jump( sf::Vector2f( 
		static_cast< float >( target.x ), 
		static_cast< float >( target.y )
	));
}

