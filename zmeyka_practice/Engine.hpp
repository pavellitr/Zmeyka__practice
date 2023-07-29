#pragma once

#include "Snake.hpp"
#include "Apple.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <iostream>

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
		Actor::Apple* apple;
		

		void input();
		void update();
		void draw();



		int is_Win = 0;

	};
}