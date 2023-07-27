#include "Apple.hpp"

Actor::Apple::Apple() {
	a_Texture = new sf::Texture;
	sf::Texture texture;
	texture.loadFromFile("Image\\Apple.png");
	*a_Texture = texture;
	a_Sprite.setTexture(*a_Texture);

	eaten = 0;

	
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

bool Actor::Apple::getEaten() {
	return eaten;
}

void Actor::Apple::update() {
	if (eaten == 1) {
		delete this;
	}
}

