#pragma once
#include "SFML/Graphics.hpp"
#include "Snake.hpp"


//#define START_X 500
//#define START_Y 500
namespace Actor {
	class Apple {
	private:
		Actor::Snake* snake;
		
		sf::Texture* a_Texture;
		sf::Sprite a_Sprite;
		sf::Vector2f a_Position;
	
		void teleport();

	public:
		
		Apple(Actor::Snake* snake);
			
		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);

		sf::Sprite getSprite();

		
		void update();


		
	};

}