#include "Snake.hpp"

Actor::Snake::Snake_chain::Snake_chain(sf::Texture texture, sf::Vector2f position) {
	m_Texture = new sf::Texture;
	*m_Texture = texture;
	m_Sprite.setTexture(*m_Texture);

	m_Position = position;
	m_Sprite.setPosition(m_Position);
}

sf::Sprite Actor::Snake::Snake_chain::getSprite() {
	return m_Sprite;
}


void Actor::Snake::Snake_chain::setPosition(sf::Vector2f pos) {
	m_Position = pos;
	m_Sprite.setPosition(m_Position);
}

sf::Vector2f Actor::Snake::Snake_chain::getPosition() {
	return m_Position;
}

////////////////////////////////////////////////////////////////////////////////////

Actor::Snake::Snake() {

	
	construct_SC();

	m_goDown = false;
	m_goUp = true;
	m_goLeft = false;
	m_goRight = false;
}

sf::Vector2f Actor::Snake::getHeadPosition() {
	return Snake_Chains[0].getPosition();
}

std::vector <sf::Sprite> Actor::Snake::getSprite() {
	std::vector <sf::Sprite> returnable;
	for (int x = 0; x < Snake_Chains.size(); x++) {
		sf::Sprite a = Snake_Chains[x].getSprite();
		returnable.push_back(a);
	}
	return returnable;
}


void Actor::Snake::construct_SC() {
	sf::Texture texture;
	texture.loadFromFile("Image\\Snake_head.png");
	Snake_chain Snake_head(texture, sf::Vector2f(START_X, START_Y));
	texture.loadFromFile("Image\\Snake_body.png");
	Snake_chain Snake_body(texture, sf::Vector2f(START_X, START_Y + SHAG));
	texture.loadFromFile("Image\\Snake_tail.png");
	Snake_chain Snake_tail(texture, sf::Vector2f(START_X, START_Y + (2 * SHAG)));
	Snake_Chains.push_back(Snake_head);
	Snake_Chains.push_back(Snake_body);
	Snake_Chains.push_back(Snake_tail);
}

void Actor::Snake::is_Left() {
	if (!m_goRight) {
		m_goLeft = true;
		m_goDown = false;
		m_goUp = false;
	}
}

void Actor::Snake::is_Down() {
	if (!m_goUp) {
		m_goDown = true;
		m_goLeft = false;
		m_goRight = false;
	}
}

void Actor::Snake::is_Right() {
	if (!m_goLeft) {
		m_goRight = true;
		m_goDown = false;
		m_goUp = false;
	}
}

void Actor::Snake::is_Up() {
	if (!m_goDown) {
		m_goUp = true;
		m_goLeft = false;
		m_goRight = false;

	}
}

void Actor::Snake::roll_massive(sf::Vector2f new_pos) {
	for (int x = Snake_Chains.size() - 1; x > 0; x--) {
		Snake_Chains[x].setPosition(Snake_Chains[x - 1].getPosition());
	}
	Snake_Chains[0].setPosition(new_pos);
}

void Actor::Snake::grow(sf::Vector2f new_pos) {
	sf::Texture texture;
	texture.loadFromFile("Image\\Snake_body.png");
	sf::Vector2f position = Snake_Chains[Snake_Chains.size() - 2].getPosition();
	Snake_chain Snake_body(texture, position);
	Snake_Chains.push_back(Snake_Chains[Snake_Chains.size() - 1]);
	Snake_Chains[Snake_Chains.size() - 2] = Snake_body;
	for (int x = Snake_Chains.size() - 3; x > 0; x--) {
		Snake_Chains[x].setPosition(Snake_Chains[x - 1].getPosition());
	}
	Snake_Chains[0].setPosition(new_pos);
}

void Actor::Snake::update() {
	if (!eated) {
		if (m_goLeft) {
			roll_massive(sf::Vector2f(Snake_Chains[0].getPosition().x - SHAG, Snake_Chains[0].getPosition().y));
		}
		if (m_goRight) {
			roll_massive(sf::Vector2f(Snake_Chains[0].getPosition().x + SHAG, Snake_Chains[0].getPosition().y));

		}
		if (m_goUp) {
			roll_massive(sf::Vector2f(Snake_Chains[0].getPosition().x, Snake_Chains[0].getPosition().y - SHAG));

		}
		if (m_goDown) {
			roll_massive(sf::Vector2f(Snake_Chains[0].getPosition().x, Snake_Chains[0].getPosition().y + SHAG));
		}
	}
	else {
		if (m_goLeft) {
			grow(sf::Vector2f(Snake_Chains[0].getPosition().x - SHAG, Snake_Chains[0].getPosition().y));

		}
		if (m_goRight) {
			grow(sf::Vector2f(Snake_Chains[0].getPosition().x + SHAG, Snake_Chains[0].getPosition().y));

		}
		if (m_goUp) {
			grow(sf::Vector2f(Snake_Chains[0].getPosition().x, Snake_Chains[0].getPosition().y - SHAG));

		}
		if (m_goDown) {
			grow(sf::Vector2f(Snake_Chains[0].getPosition().x, Snake_Chains[0].getPosition().y + SHAG));
		}
		eated = false;
	}
}

void Actor::Snake::grows_Snake() {
	eated = true;
}

