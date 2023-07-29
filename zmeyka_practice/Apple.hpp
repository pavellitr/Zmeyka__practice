#pragma once
#include "SFML/Graphics.hpp"
#include "Snake.hpp"


namespace Actor {
	class Apple {
	private:
		Actor::Snake* snake;
		
		sf::Texture* a_Texture;
		sf::Sprite a_Sprite;
		sf::Vector2f a_Position;
		int points;
	
		void teleport();

	public:
		
		Apple(Actor::Snake* snake);
			
		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);

		int getPoints();

		sf::Sprite getSprite();
		void setPoints(int x);
		
		void update();


		
	};

}