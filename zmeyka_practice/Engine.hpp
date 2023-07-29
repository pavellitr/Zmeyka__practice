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
		
		sf::Sprite win_sprite;
		sf::Texture win_texture;

		sf::Sprite lose_sprite;
		sf::Texture lose_texture;

		Actor::Snake* snake;
		Actor::Apple* apple;
		
		sf::Font font;
		sf::Text* text;
		void input();
		void update();
		void draw();
		void restart();
		void getPoint();

		int is_Win = 0;

	};
}