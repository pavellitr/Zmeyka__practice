#pragma once

#include "SFML/Graphics.hpp"
#include <vector>


#define START_X 320
#define START_Y 320
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
		std::vector <sf::Vector2f> Snake_Pos;

		void construct_SC();
		void roll_massive(sf::Vector2f new_pos);
		void grow(sf::Vector2f new_pos);

		bool m_goRight;
		bool m_goUp;
		bool m_goDown;
		bool m_goLeft;
		bool eated;
		bool is_Changed;
		bool is_Dead;

	public:
		Snake();

		void grows_Snake();
		void is_Left();
		void is_Down();
		void is_Right();
		void is_Up();
		bool getDead();

		std::vector <sf::Vector2f> getPos();
		std::vector <sf::Sprite> getSprite();
		sf::Vector2f getHeadPosition();
		int getSize();

		void update();

	};
}
