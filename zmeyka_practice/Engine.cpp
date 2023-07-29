#include "Engine.hpp"



Engine_mod::Engine::Engine() { //����������� ������
	m_Window.create(sf::VideoMode(1000, 1000), "Snake Game"); //������� ����

	font.loadFromFile("font\\big-shot.ttf"); //��������� ����� ��� �����
	text = new sf::Text("", font, 20);  //������� ����� �����


	snake = new Actor::Snake(); //������� ����
	apple = new Actor::Apple(snake); //������ ������

	this->win_texture.loadFromFile("Image\\You_Win.png"); //��������� �������� ��� ������ ������
	this->win_sprite.setTexture(win_texture); //������� ������ ��� ������ ������

	this->lose_texture.loadFromFile("Image\\You_Lose.png"); //��������� �������� ��� ������ ���������
	this->lose_sprite.setTexture(lose_texture); //������� ������ ��� ������ ���������



	this->m_BackgroundTexture.loadFromFile("Image\\myWorld.png"); //��������� �������� �������
	this->m_BackgroundSprite.setTexture(m_BackgroundTexture); //������� ������ �������
}

void Engine_mod::Engine::start() {

	sf::Clock clockUpdate; //������� ������
	while (m_Window.isOpen()) {
		if (is_Win == 0) { //���� is_Win � ����������� ��������� �������� �������� ���� ����
			sf::Event event;
			while (m_Window.pollEvent(event)) //�������� �� �������
			{
				if (event.type == sf::Event::Closed) //�������� �� ������� ���������
					m_Window.close(); //��������� ����
			}

			input(); //����� ����

			sf::Int32 dU = clockUpdate.getElapsedTime().asMilliseconds();  //������� ����� � �������

			if (dU >= 100) { //10 ��� � ������� ���������� ��������� ������� ������
				update(); //���������� ������� ������
				clockUpdate.restart(); //��������� ������
			}

			draw(); //������������ ��� ��������
			if (snake->getSize() == 50) { //�������� �� ���������� ������� � 50 �����
				is_Win = 1; //��������� ��������� �� ������
			}
			else if (snake->getDead()) { //�������� �� ������ ������
				is_Win = -1; //��������� ��������� �� ��������
			}
		}
		else if (is_Win == 1) { //���� is_Win � ��������� ������


			m_Window.clear(sf::Color::White); //������� ����
			
			m_Window.draw(win_sprite); //������ ������ ����� ������
			m_Window.display(); //������� �� ����� ��, ��� ����������
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //���� �������� Esc ���� �����������
			{
				m_Window.close(); //��������� ����
			}

			sf::Event event; 
			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
					m_Window.close();
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //���� �������� Space �� �������
			{
				restart();
			}

		}
		else if (is_Win == -1) { //�� �� ����� ��� � ������, ������ ������� ����� ���������
			m_Window.clear(sf::Color::White);

			m_Window.draw(lose_sprite);
			m_Window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{


				m_Window.close();
			}

			sf::Event event;
			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_Window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				restart();
			}
		}
	}
}

void Engine_mod::Engine::update() { //�����  ����������� ������

	snake->update(); //�� ����� � ��� ����

	apple->update();

	getPoint(); //������ �������� ����
}
void Engine_mod::Engine::draw() { //����� ��� ��������� ����� (��� �������� ���� �������)
	m_Window.clear(sf::Color::White);

	m_Window.draw(m_BackgroundSprite);

	m_Window.draw(apple->getSprite());

	std::vector <sf::Sprite> Buffer = snake->getSprite();
	for (int x = 0; x < Buffer.size(); x++) {
		m_Window.draw(Buffer[x]);
	}

	m_Window.draw(*text);

	m_Window.display();

}

void Engine_mod::Engine::input() { //���� ��� ���������� � �����

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //����� �� Esc
	{
		m_Window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { //����� �� �
		snake->is_Left();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //������ �� D
		snake->is_Right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //����� �� W
		snake->is_Up();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //���� �� S
		snake->is_Down();
	}



}

void Engine_mod::Engine::restart() {
	apple->setPoints(0);
	delete snake;
	delete apple;

	snake = new Actor::Snake();
	apple = new Actor::Apple(snake);

	is_Win = 0;
}

void Engine_mod::Engine::getPoint() {
	std::string s = std::to_string(apple->getPoints());
	text->setString("Points: " + s);
	text->setPosition(40, 40);
}