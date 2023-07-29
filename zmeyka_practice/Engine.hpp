#pragma once

#include "Snake.hpp"
#include "Apple.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

namespace Engine_mod {
	class Engine
	{
	public:
		Engine();

		void start();

	private:
		sf::RenderWindow m_Window;

		sf::Sprite m_BackgroundSprite;
		sf::Texture m_BackgroundTexture;

		Actor::Snake* snake;
		std::vector <Actor::Apple*> Apples;

		void input();
		void update();
		void draw();
		void addApple();
		

	};
}