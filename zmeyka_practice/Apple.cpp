#include "Apple.hpp"
#include "stdlib.h"
#include "time.h"
Actor::Apple::Apple(Actor::Snake* snake) {
	this->snake = snake;

	a_Texture = new sf::Texture;
	sf::Texture texture;
	texture.loadFromFile("Image\\Apple.png");
	*a_Texture = texture;
	a_Sprite.setTexture(*a_Texture);

	a_Position = sf::Vector2f(280, 160);
	a_Sprite.setPosition(sf::Vector2f(280,160));
 

}

sf::Vector2f Actor::Apple::getPosition() {
	return a_Position;
}

void Actor::Apple::setPosition(sf::Vector2f pos) {
	a_Position = pos;
	a_Sprite.setPosition(a_Position);
}

sf::Sprite Actor::Apple::getSprite() {
	return a_Sprite;
}

float RandomNumber(int min, int max) {
	srand(time(NULL));
	float num = min + rand() % (max - min + 1);
    return num;
}


void Actor::Apple::update() {
	if (snake->getHeadPosition() == a_Position) {

	snake->grows_Snake();
		
		
	srand(time(NULL));
	float randX = 40 * ( rand() % 24);
	float randY = 40 * ( rand() % 24 );
	sf::Vector2f proverka = sf::Vector2f(randX, randY);
	a_Position = proverka;
    a_Sprite.setPosition(a_Position);
	}

}


