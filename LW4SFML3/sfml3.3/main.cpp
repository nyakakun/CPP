#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr float WidthEye = 70;			 //ширина глаза
constexpr float HeightEye = 50;			 //высота глаза
constexpr float RadiusPupil = 15;		 //Радиус зрачок
constexpr float DistBetEyeAndPupil = 10; //дистанция от края глаза до края зрачка
constexpr float DistanceBetweenEye = 50; //дистанция между глазамиdsfsfsdfsdf
constexpr float Points = 900;			 //кол-во точек элипса
constexpr unsigned WINDOW_WIDTH = 800;   //ширина окна
constexpr unsigned WINDOW_HEIGHT = 600;  //высота окна

struct Eye //элементы глаза
{
	sf::ConvexShape eyeApple;											   //"глазное яблоко"
	sf::CircleShape eyePupil;											   //"зрачок"
	sf::Vector2f position;												   //позиция глаза
	void init(float RadiusPupil, sf::Vector2f position, sf::Vector2f size) //инициализация глаза
	{
		eyeApple.setPosition(position); //позиция "глазного яблока"
		this->position = position;		//установка позиции глаза, чтобы знать вокруг чего вращаться
		eyeApple.setPointCount(Points); //кол-во вершин глаза

		for (int pointNo = 0; pointNo < Points; ++pointNo)
		{
			float angle = float(2 * M_PI * pointNo) / float(Points);	 //угол точки для элипса
			sf::Vector2f point = sf::Vector2f{							 //позиция точки
											  size.y * std::sin(angle),  //позиция по y
											  size.x * std::cos(angle)}; //позиция по x
			eyeApple.setPoint(pointNo, point);							 //установка точки
		}
		eyePupil.setRadius(RadiusPupil);														  //задаем радиус зрачка
		eyePupil.setPosition(sf::Vector2f({position.x - RadiusPupil, position.y - RadiusPupil})); //задаем позицию зрачка
		eyeApple.setFillColor(sf::Color(0xFF, 0x0, 0x0));										  //цвет яблока
		eyePupil.setFillColor(sf::Color(0x0, 0x0, 0x0));										  //цвет зрачка
	};

	void update(sf::Vector2f &mousePosition) //функция обновления позиции мыши
	{
		const sf::Vector2f delta = mousePosition - position; //позиция курсора относительно центра глаза
		const float angle = atan2(delta.x, delta.y);		 //угол курсора относительно центра глаза

		float Sin1 = (/*YOffset - */ HeightEye + (RadiusPupil + DistBetEyeAndPupil)) * std::sin(angle);
		float Sin2 = (/*YOffset - */ HeightEye + (RadiusPupil + DistBetEyeAndPupil)) * std::sin(angle - M_PI);
		float Cos1 = (/*XOffset - */ WidthEye + (RadiusPupil + DistBetEyeAndPupil)) * std::cos(angle);
		float Cos2 = (/*XOffset - */ WidthEye + (RadiusPupil + DistBetEyeAndPupil)) * std::cos(angle - M_PI);

		/*float YOffset = 0;
		float YOffset = 0;*/
		int flag = 1;
		if ((delta.y <= std::max(Sin1, Sin2)) && (delta.y >= std::min(Sin1, Sin2)))
		{
			if ((delta.x <= std::max(Cos1, Cos2)) && (delta.x >= std::min(Cos1, Cos2)))
			{
				eyePupil.setPosition(mousePosition - sf::Vector2f({RadiusPupil, RadiusPupil}));
				flag = 0;
				std::cout << "перетаскваю мышью" << std::endl;
			}
		}
		if (flag == 1)
		{
			const sf::Vector2f offsetPupil = {																					 //смещение зрачка относительно центра глаза
											  (/*YOffset - */ HeightEye - (RadiusPupil + DistBetEyeAndPupil)) * std::sin(angle), //смещение по y
											  (/*XOffset - */ WidthEye - (RadiusPupil + DistBetEyeAndPupil)) * std::cos(angle)}; //смещение по Х
			eyePupil.setPosition((position - sf::Vector2f({RadiusPupil, RadiusPupil})) + offsetPupil);							 //позиция зрачка
		}
	};

	void draw(sf::RenderWindow &window) //функция отрисовки глаза
	{
		window.draw(eyeApple); //
		window.draw(eyePupil); //
	}
};

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition) //функция получения/сохранения координат мыши
{
	mousePosition = {float(event.x), float(event.y)}; //
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition) //основной цикл программы
{
	sf::Event event;
	while (window.pollEvent(event)) //
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:						 //если пользователь двинул мышь
			onMouseMove(event.mouseMove, mousePosition); //сохраняем координаты
			break;
		default:
			break;
		}
	}
}

int main() //
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
							"These EYES see your cursor",
							sf::Style::Default,
							settings);
	sf::Vector2f mousePosition;

	Eye leftEye;  //левый глаз
	Eye RightEye; //правый глаз

	float XLeft = (WINDOW_WIDTH / 2) - WidthEye - (DistanceBetweenEye / 2);  //Х позиция левого глаза
	float XRight = (WINDOW_WIDTH / 2) + WidthEye + (DistanceBetweenEye / 2); //Х позиция правого глаза

	float YLeft = (WINDOW_HEIGHT / 2) - HeightEye;  //У позиция левого глаза
	float YRight = (WINDOW_HEIGHT / 2) - HeightEye; //У позиция правого глаза

	leftEye.init(RadiusPupil, sf::Vector2f({XLeft, YLeft}), sf::Vector2f({WidthEye, HeightEye}));	//инициализация левого глаза
	RightEye.init(RadiusPupil, sf::Vector2f({XRight, YRight}), sf::Vector2f({WidthEye, HeightEye})); //инициализация правго глаза
	while (window.isOpen())																			 //
	{
		pollEvents(window, mousePosition);
		leftEye.update(mousePosition);  //обновляем левый глаз
		RightEye.update(mousePosition); //обновляем правый
		window.clear();
		leftEye.draw(window);  //отрисока левого
		RightEye.draw(window); //отрисовка правого глаза
		window.display();
	}
}