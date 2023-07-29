#include "Engine.hpp"



Engine_mod::Engine::Engine() { //конструктор класса
	m_Window.create(sf::VideoMode(1000, 1000), "Snake Game"); //создаем окно

	font.loadFromFile("font\\big-shot.ttf"); //загружаем шрифт для счёта
	text = new sf::Text("", font, 20);  //создаем текст счета


	snake = new Actor::Snake(); //создаем змею
	apple = new Actor::Apple(snake); //создаю яблоко

	this->win_texture.loadFromFile("Image\\You_Win.png"); //загружаем текстуру для экрана победы
	this->win_sprite.setTexture(win_texture); //создаем спрайт для экрана победы

	this->lose_texture.loadFromFile("Image\\You_Lose.png"); //загружаем текстуру для экрана проигрыша
	this->lose_sprite.setTexture(lose_texture); //создаем спрайт для экрана проигрыша



	this->m_BackgroundTexture.loadFromFile("Image\\myWorld.png"); //загружаем текстуру задника
	this->m_BackgroundSprite.setTexture(m_BackgroundTexture); //создаем спрайт задника
}

void Engine_mod::Engine::start() {

	sf::Clock clockUpdate; //создаем таймер
	while (m_Window.isOpen()) {
		if (is_Win == 0) { //пока is_Win в нейтральном состоянии работает основное тело игры
			sf::Event event;
			while (m_Window.pollEvent(event)) //проверка на события
			{
				if (event.type == sf::Event::Closed) //проверка на нажатие креститка
					m_Window.close(); //Закрываем окно
			}

			input(); //метод ввод

			sf::Int32 dU = clockUpdate.getElapsedTime().asMilliseconds();  //снимаем время с таймера

			if (dU >= 100) { //10 раз в секунду обноовляем состояние игровой логики
				update(); //обновление игровой логики
				clockUpdate.restart(); //рестартим таймер
			}

			draw(); //отрисовываем всю картинку
			if (snake->getSize() == 50) { //проверка на достижение размера в 50 ячеек
				is_Win = 1; //назначает состояние на победу
			}
			else if (snake->getDead()) { //проверка на смерть змейки
				is_Win = -1; //назначает состояние на проигрыш
			}
		}
		else if (is_Win == 1) { //если is_Win в состоянии победа


			m_Window.clear(sf::Color::White); //очищаем окно
			
			m_Window.draw(win_sprite); //рисуем спрайт экран победы
			m_Window.display(); //выводим на экран то, что отрисовали
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //если нажимаем Esc окно закрывается
			{
				m_Window.close(); //закрываем окно
			}

			sf::Event event; 
			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
					m_Window.close();
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //если нажимаем Space то рестарт
			{
				restart();
			}

		}
		else if (is_Win == -1) { //то же самое что и победа, только выводит экран поражения
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

void Engine_mod::Engine::update() { //метод  обновляющий логику

	snake->update(); //по моему и так ясно

	apple->update();

	getPoint(); //короче собираем счет
}
void Engine_mod::Engine::draw() { //метод для отрисовки всего (как работает сами поймете)
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

void Engine_mod::Engine::input() { //мето для считывания с клавы

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //выход на Esc
	{
		m_Window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { //влево на А
		snake->is_Left();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //вправо на D
		snake->is_Right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //вверх на W
		snake->is_Up();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //вниз на S
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