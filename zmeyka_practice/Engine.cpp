#include "Engine.hpp"



Engine_mod::Engine::Engine() {
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;

	m_Window.create(sf::VideoMode(1000, 1000), "Snake Game");


	snake = new Actor::Snake();
	apple = new Actor::Apple(snake);

	this->m_BackgroundTexture.loadFromFile("Image\\myWorld.png");
	this->m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

void Engine_mod::Engine::start() {

	sf::Clock clockUpdate;
	while (m_Window.isOpen()) {

		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_Window.close();
		}

		input();

		sf::Int32 dU = clockUpdate.getElapsedTime().asMilliseconds();

		if (dU >= 500) {
			update();
			clockUpdate.restart();
		}

		draw();
	}
}

void Engine_mod::Engine::update() {

	snake->update();

	apple->update();
}
void Engine_mod::Engine::draw() {
	m_Window.clear(sf::Color::White);

	m_Window.draw(m_BackgroundSprite);

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