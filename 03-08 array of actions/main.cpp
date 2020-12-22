#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "square.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:

	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition([ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition([ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }),
		work(work)
	{}

	action(
		ball balletje,
		square muur0,
		square muur1,
		square muur2,
		square muur3,
		square vierkantje,
		std::function< void() > work
	) :
		condition([balletje, muur0, muur1, muur2, muur3, vierkantje]()->bool { 
		if (!balletje.cirkel.getGlobalBounds().intersects(muur0.rectangle.getGlobalBounds()) ||
			!balletje.cirkel.getGlobalBounds().intersects(muur1.rectangle.getGlobalBounds()) ||
			!balletje.cirkel.getGlobalBounds().intersects(muur2.rectangle.getGlobalBounds()) ||
			!balletje.cirkel.getGlobalBounds().intersects(muur3.rectangle.getGlobalBounds()) ||
			!balletje.cirkel.getGlobalBounds().intersects(vierkantje.rectangle.getGlobalBounds())
			) {
			return 1;
		}
		else {
			return 0;
		}
		}),
		work(work)
	{}

	action(
		ball &balletje,
		square &muur,
		std::function<void()> work
	) :
		condition([&]()->bool { if (balletje.cirkel.getGlobalBounds().intersects(muur.rectangle.getGlobalBounds())) {
												//std::cout << "if statement is true" << std::endl;
												return 1;
											} else {
												//std::cout << "if statement is false" << std::endl;
												return 0;
											}}),
		work(work)
	{}


	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main(int argc, char *argv[]) {
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 } }; //a ball
	square my_square(sf::Vector2f{ 90.0, 60.0 }, sf::Vector2f{ 50.0, 50.0 }, sf::Color::Green); //a square
	square my_wall0(sf::Vector2f{ 640.0, 30.0 }); //top wall
	square my_wall1(sf::Vector2f{ 30.0, 480.0 }); //left wall
	square my_wall2(sf::Vector2f{ 640.0, 30.0 }, sf::Vector2f{ 0.0, 450.0}); //bottom wall
	square my_wall3(sf::Vector2f{ 30.0, 480.0 }, sf::Vector2f{ 610.0, 0.0 }); //right wall

	sf::Vector2f richting = sf::Vector2f{ 1.0, 1.0 };

	action actions[] = {
		action(sf::Keyboard::Left,  [&]() { my_square.move(sf::Vector2f(-1.0,  0.0)); }),
		action(sf::Keyboard::Right, [&]() { my_square.move(sf::Vector2f(+1.0,  0.0)); }),
		action(sf::Keyboard::Up,    [&]() { my_square.move(sf::Vector2f(0.0, -1.0)); }),
		action(sf::Keyboard::Down,  [&]() { my_square.move(sf::Vector2f(0.0, +1.0)); }),
		action(sf::Mouse::Left,     [&]() { my_square.jump(sf::Mouse::getPosition(window)); }),
		action(my_ball, my_wall0, my_wall1, my_wall2, my_wall3, my_square, [&]() { my_ball.move(richting); }),
		action(my_ball, my_wall0,   [&]() { richting.y *= -1; my_ball.move(richting); }),
		action(my_ball, my_wall1,   [&]() { richting.x *= -1; my_ball.move(richting); }),
		action(my_ball, my_wall2,   [&]() { richting.y *= -1; my_ball.move(richting); }),
		action(my_ball, my_wall3,   [&]() { richting.x *= -1; my_ball.move(richting); }),
		action(my_ball, my_square,  [&]() { if (my_square.getPosition().x > my_ball.getPosition().x && my_square.getPosition().y > my_ball.getPosition().y) {
												if ((my_square.getPosition().x - my_ball.getPosition().x) <= -50) {
													richting.x *= -1;
												} else if (my_square.getPosition().y - my_ball.getPosition().y >= -50) {
													 richting.y *= -1;
												}
												} else if (my_square.getPosition().x < my_ball.getPosition().x && my_square.getPosition().y < my_ball.getPosition().y) {
													richting.y *= -1;
												} else if (my_square.getPosition().x < my_ball.getPosition().x && my_square.getPosition().y > my_ball.getPosition().y) {
													richting.x *= -1;
												} else if (my_square.getPosition().x > my_ball.getPosition().x && my_square.getPosition().y < my_ball.getPosition().y) {
													richting.y *= -1;
												}
										  })
	};
	 while (window.isOpen()) {
		for( auto & action : actions ){
			action();
		}
		
		if (my_ball.cirkel.getGlobalBounds().intersects(my_wall2.rectangle.getGlobalBounds())) {
			std::cout << "ball collided met wall, richting: " << richting.x << "," << richting.y << std::endl;
		}
		
		window.clear();
		my_ball.draw( window );
		my_square.draw( window );
		my_wall0.draw(window);
		my_wall1.draw(window);
		my_wall2.draw(window);
		my_wall3.draw(window);
		window.display();

		sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	
	}

	std::cout << "Terminating application\n";
	return 0;
}

