#include "Apple.hpp"
#include "stdlib.h"
#include "time.h"

Actor::Apple::Apple(Actor::Snake* snake) { // ����������� ������
	this->snake = snake;
	//���������� ��������� � ��������
	a_Texture = new sf::Texture;  
	sf::Texture texture;
	texture.loadFromFile("Image\\Apple.png");
	*a_Texture = texture;
	a_Sprite.setTexture(*a_Texture);
	
	//��������� �������������� ������ 
	float randX = 40 * (rand() % 24);
	float randY = 40 * (rand() % 24);
	a_Position = sf::Vector2f(randX, randY);
	a_Sprite.setPosition(sf::Vector2f(randX,randY));
	
	//��������� ���-�� �����
	points = 0;

}
//�������, ������������ �������������� ������ � ������� ��������� Vector2f
sf::Vector2f Actor::Apple::getPosition() {
	return a_Position;
}
//�������, �������� �������������� ������ � ������� ��������� Vector2f
void Actor::Apple::setPosition(sf::Vector2f pos) {
	a_Position = pos;
	a_Sprite.setPosition(a_Position);
}
//�������, ������������ ������
sf::Sprite Actor::Apple::getSprite() {
	return a_Sprite;
}
//�������, ���������� �� ��������� ������ ������ ����� �������� �����������
void Actor::Apple::teleport() {
	srand(time(NULL));
	float randX = 40 * (rand() % 24);
	float randY = 40 * (rand() % 24);
	sf::Vector2f proverka = sf::Vector2f(randX, randY);
	std::vector <sf::Vector2f>  chains = snake->getPos();
	int i = 0, tpx = 40;
	int flag = 0;
	do
	{
		for (i = 0; i < chains.size(); i++) {
			if (proverka == chains[i]) { flag = 1; i = chains.size() - 1; }
		}

		if (flag == 1) {
			proverka.x = proverka.x - tpx;

			if (proverka.x - tpx < 0 || proverka.x + tpx>960) {
				proverka.y = 40 * (rand() % 24);
				proverka.x = 40 * (rand() % 24);
				tpx = 40;
			}

			if (tpx > 0) tpx = -tpx - 40;
			if (tpx < 0) tpx = -tpx + 40;

			flag = 0;
		}

	} while (flag != 0);


	a_Position = proverka;
	a_Sprite.setPosition(a_Position);
	
}
//������� ������������ ���������� �����
int Actor::Apple::getPoints() {
	return points;
}
//�������,���������� �� ��� ������ �������� ������
void Actor::Apple::update() {
	if (snake->getHeadPosition() == a_Position) {
		 snake->grows_Snake();
		 teleport();
		 points = points+1;
		
	
	}

}
// ������������� ������������ X �����
void Actor::Apple::setPoints(int x) {
	points = x;
}


