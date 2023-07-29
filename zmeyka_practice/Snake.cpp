#include "Snake.hpp"

//это логика Snake_chain

Actor::Snake::Snake_chain::Snake_chain(sf::Texture texture, sf::Vector2f position) {
	m_Texture = new sf::Texture; //указатель нужен, чтобы текстурка не удалялась из памяти иначе текстурка не отображается
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

//это логика Snake

Actor::Snake::Snake() {

	
	construct_SC(); //собираем змейку

	m_goDown = false;
	m_goUp = true;
	m_goLeft = false;
	m_goRight = false;

	is_Dead = false;
}

sf::Vector2f Actor::Snake::getHeadPosition() {
	return Snake_Chains[0].getPosition();
}

std::vector <sf::Sprite> Actor::Snake::getSprite() { //собираем вектор вытаскивая спрайты из ячеек
	std::vector <sf::Sprite> returnable; 
	for (int x = 0; x < Snake_Chains.size(); x++) {
		sf::Sprite a = Snake_Chains[x].getSprite();
		returnable.push_back(a);
	}
	return returnable;
}

std::vector <sf::Vector2f> Actor::Snake::getPos() {
	return Snake_Pos;
}


void Actor::Snake::construct_SC() { //создаем 3 ячейки загоняем их в вектор, вытаскиваем из них позиции и загоняем в другой вектор
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
	Snake_Pos.push_back(Snake_head.getPosition());
	Snake_Pos.push_back(Snake_body.getPosition());
	Snake_Pos.push_back(Snake_tail.getPosition());
}


void Actor::Snake::is_Left() { //переключают состояние направления
	if (!m_goRight && !is_Changed) {
		m_goLeft = true;
		m_goDown = false;
		m_goUp = false;
		is_Changed = true;
	}
}

void Actor::Snake::is_Down() {
	if (!m_goUp && !is_Changed) {
		m_goDown = true;
		m_goLeft = false;
		m_goRight = false;
		is_Changed = true;
	}
}

void Actor::Snake::is_Right() {
	if (!m_goLeft && !is_Changed) {
		m_goRight = true;
		m_goDown = false;
		m_goUp = false;
		is_Changed = true;
	}
}

void Actor::Snake::is_Up() {
	if (!m_goDown && !is_Changed) {
		m_goUp = true;
		m_goLeft = false;
		m_goRight = false;
		is_Changed = true;

	}
}

void Actor::Snake::roll_massive(sf::Vector2f new_pos) { //новую позуцию вставляем в голову, остальные координаты сдвигаем от головы к хвосту
	for (int x = 0; x < Snake_Pos.size() - 1; x++) {
		if (new_pos == Snake_Pos[x]) {
			is_Dead = true;
			x = Snake_Pos.size() - 2;
		}
	}
	if (!is_Dead) {

		for (int x = Snake_Chains.size() - 1; x > 0; x--) { //сдвигаем позиции от головы к хвосту, старую позицию хвоста удаляем
			Snake_Chains[x].setPosition(Snake_Chains[x - 1].getPosition());
			Snake_Pos[x] = Snake_Pos[x - 1];
		}

		if (new_pos.x > 960) { //телепорты от стены к стене
			new_pos.x -= 1000;
		}
		if (new_pos.y > 960) {
			new_pos.y -= 1000;
		}
		if (new_pos.x < 0) {
			new_pos.x += 1000;
		}
		if (new_pos.y < 0) {
			new_pos.y += 1000;
		}
		Snake_Chains[0].setPosition(new_pos); //новую позицию в голову
		Snake_Pos[0] = new_pos; //записываем новую позицию в вектор позиций
	}
}

void Actor::Snake::grow(sf::Vector2f new_pos) { //то же самое только теперь змейка еще и растет 
	for (int x = 0; x < Snake_Pos.size(); x++) { //проверка на столкновение
		if (new_pos == Snake_Pos[x]) {
			is_Dead = true;
			x = Snake_Pos.size() - 1;
		}
	}
	if (!is_Dead) {
		sf::Texture texture;
		texture.loadFromFile("Image\\Snake_body.png"); //создаем ячейку

		sf::Vector2f position = Snake_Chains[Snake_Chains.size() - 2].getPosition();
		Snake_chain Snake_body(texture, position);

		Snake_Chains.push_back(Snake_Chains[Snake_Chains.size() - 1]); //загоняем новую ячейку прям перед хвостом
		Snake_Pos.push_back(Snake_Pos[Snake_Pos.size() - 1]); 

		Snake_Chains[Snake_Chains.size() - 2] = Snake_body;
		Snake_Pos[Snake_Pos.size() - 2] = position;

		for (int x = Snake_Chains.size() - 3; x > 0; x--) { //сдвигаем все от головы до 3 элемента с конца, чтобы свежедобавленная ячейка и хвост остались на месте
			Snake_Chains[x].setPosition(Snake_Chains[x - 1].getPosition());
			Snake_Pos[x] = Snake_Pos[x - 1];
		}

		if (new_pos.x > 960) {
			new_pos.x -= 1000;
		}
		if (new_pos.y > 960) {
			new_pos.y -= 1000;
		}
		if (new_pos.x < 0) {
			new_pos.x += 1000;
		}
		if (new_pos.y < 0) {
			new_pos.y += 1000;
		}

		Snake_Chains[0].setPosition(new_pos);
		Snake_Pos[0] = new_pos;
	}
}

void Actor::Snake::update() { //и так поймете
	if (!eated && !is_Dead) {
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
	else if (eated && !is_Dead) {
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
	is_Changed = false;
}

void Actor::Snake::grows_Snake() {
	eated = true;
}

int Actor::Snake::getSize() {
	return Snake_Chains.size();
}

bool Actor::Snake::getDead() {
	return is_Dead;
}