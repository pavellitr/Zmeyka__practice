#pragma once

#include "SFML/Graphics.hpp"
#include <vector>


#define START_X 320
#define START_Y 320
#define SHAG 40

namespace Actor {
	class Snake { //короче, змейка состоит из €чеек и кажда€ €чейка это экземпл€р класса Snake_chain (дальше буду называть €чейками)
	private:
		class Snake_chain {
		private:
			sf::Texture* m_Texture;
			sf::Sprite m_Sprite;
			sf::Vector2f m_Position; //позици€ €чейки змеи

		public:
			Snake_chain(sf::Texture texture, sf::Vector2f position);

			void setPosition(sf::Vector2f pos);
			sf::Vector2f getPosition();
			
			sf::Sprite getSprite();
		};

		std::vector <Snake::Snake_chain> Snake_Chains; //вектор €чеек 
		std::vector <sf::Vector2f> Snake_Pos; //вектор позиций €чеек

		void construct_SC(); //собирает начальную змейку из головы, тела и хвоста
		void roll_massive(sf::Vector2f new_pos); //отвечает за перемещение змейки
		void grow(sf::Vector2f new_pos); //то же самое но еще и растет

		bool m_goRight;
		bool m_goUp;
		bool m_goDown;
		bool m_goLeft;
		bool eated;
		bool is_Changed;
		bool is_Dead;

	public:
		Snake();

		void grows_Snake(); //заставл€ет змейку расти
		void is_Left(); //мен€ют направление
		void is_Down();
		void is_Right();
		void is_Up();
		bool getDead(); //запрашивает мертва ли змейка

		std::vector <sf::Vector2f> getPos(); //возвращает вектора позиций и спрайтов
		std::vector <sf::Sprite> getSprite();
		sf::Vector2f getHeadPosition(); //возвращает координату головы змейки
		int getSize(); //возвращает кол-во €чеек

		void update(); //обновл€ет состо€ние змейки

	};
}
