#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

#define START_X 300
#define START_Y 300
#define SHAG 40

namespace Actor {
	class Snake {
	private:
		class Snake_chain {
		private:
			sf::Texture* m_Texture;
			sf::Sprite m_Sprite;
			sf::Vector2f m_Position;

		public:
			Snake_chain(sf::Texture texture, sf::Vector2f position);

			void setPosition(sf::Vector2f pos);
			sf::Vector2f getPosition();

			sf::Sprite getSprite();
		};

		std::vector <Snake::Snake_chain> Snake_Chains;


		void construct_SC();
		void roll_massive(sf::Vector2f new_pos);



		bool m_goRight;
		bool m_goUp;
		bool m_goDown;
		bool m_goLeft;

	public:
		Snake();

		void is_Left();
		void is_Down();
		void is_Right();
		void is_Up();

		std::vector <sf::Sprite> getSprite();
		sf::Vector2f getHeadPosition();

		void update();

	};
}
