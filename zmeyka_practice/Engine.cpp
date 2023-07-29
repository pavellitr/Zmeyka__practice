#include "Engine.hpp"



Engine_mod::Engine::Engine() {
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;

	m_Window.create(sf::VideoMode(1000, 1000), "Snake Game");


	snake = new Actor::Snake();
	apple = new Actor::Apple(snake);

	this->win_texture.loadFromFile("Image\\blue.png");
	this->win_sprite.setTexture(win_texture);

	this->lose_texture.loadFromFile("Image\\red.jpg");
	this->lose_sprite.setTexture(lose_texture);



	this->m_BackgroundTexture.loadFromFile("Image\\myWorld.png");
	this->m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

void Engine_mod::Engine::start() {

	sf::Clock clockUpdate;
	while (m_Window.isOpen()) {
		if (is_Win == 0) {
			sf::Event event;
			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_Window.close();
			}

			input();

			sf::Int32 dU = clockUpdate.getElapsedTime().asMilliseconds();

			if (dU >= 100) {
				update();
				clockUpdate.restart();
			}

			draw();
			if (snake->getSize() == 5) {
				is_Win = 1;
			}
		}
		else if (is_Win == 1) {


			m_Window.clear(sf::Color::White);
			
			m_Window.draw(win_sprite);
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

		}
		else if (is_Win == -1) {
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

		}
	}
}

void Engine_mod::Engine::update() {

	snake->update();

	apple->update();
}
void Engine_mod::Engine::draw() {
	m_Window.clear(sf::Color::White);

	m_Window.draw(m_BackgroundSprite);

	
	sf::Font font;
	font.loadFromFile("font\\Arial.ttf");
	sf::Text text("", font, 20); 
	std::string s = std::to_string(apple->getPoints());
	text.setString("Points:" + s );
	text.setPosition(40, 40);
	m_Window.draw(text);

	sf::Sprite  Yabloko = apple->getSprite();
	m_Window.draw(Yabloko);

	std::vector <sf::Sprite> Buffer = snake->getSprite();
	for (int x = 0; x < Buffer.size(); x++) {
		m_Window.draw(Buffer[x]);
	}

	m_Window.display();

}

void Engine_mod::Engine::input() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_Window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		snake->is_Left();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		snake->is_Right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		snake->is_Up();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		snake->is_Down();
	}



}