#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

float toGrees(float radians){ return float(double(radians) * 180.0 / M_PI); }

constexpr float WidthEye = 70;			 //ширина глаза
constexpr float HeightEye = 100;			 //высота глаза
constexpr float RadiusPupil = 15;		 //Радиус зрачок
constexpr float DistBetEyeAndPupil = 20; //дистанция от края глаза до центра зрачка
constexpr float DistanceBetweenEye = 50; //дистанция между глазами
constexpr float Points = 100;			 //кол-во точек элипса
constexpr unsigned WINDOW_WIDTH = 800;   //ширина окна
constexpr unsigned WINDOW_HEIGHT = 600;  //высота окна
const sf::Color ColorApple = sf::Color(0xFF, 0x0, 0x0);  //цвет яблока глозного
const sf::Color ColorPupil = sf::Color(0x0, 0xFF, 0x0);  //зрачка глазного цвет это ©Йода

struct Eye{
	sf::ConvexShape eyeApple; //"глазное яблоко"
	sf::CircleShape eyePupil; //"зрачок"
	sf::Vector2f position;	//позиция глаза

	void init(sf::Vector2f position,sf::Vector2f size);
	void draw(sf::RenderWindow &window);
	void update(sf::Vector2f &mousePosition);
private:
	float calcAngle(sf::Vector2f &mousePosition);
};

float Eye::calcAngle(sf::Vector2f &mousePosition)
{
	const sf::Vector2f delta = mousePosition - this->position;
	const sf::Vector2f modifiedDelta = sf::Vector2f({delta.x / (WidthEye-DistBetEyeAndPupil), delta.y / (HeightEye-DistBetEyeAndPupil)});
	return std::atan2(modifiedDelta.y, modifiedDelta.x);
};

void Eye::update(sf::Vector2f &mousePosition)
{
	float angle = calcAngle(mousePosition);
	sf::Vector2f pepe = sf::Vector2f{
		(WidthEye-DistBetEyeAndPupil) * std::cos(angle),
		(HeightEye-DistBetEyeAndPupil) * std::sin(angle)
	};

	this->eyePupil.setPosition(this->position + pepe);
}

void Eye::draw(sf::RenderWindow &window)
{
	window.draw(eyeApple);
	window.draw(eyePupil);
}

void Eye::init(sf::Vector2f position,sf::Vector2f size)
{
	this->eyeApple.setPosition(position); //позиция "глазного яблока"
	this->position = position;		//установка позиции глаза, чтобы знать вокруг чего вращаться
	this->eyeApple.setPointCount(Points); //кол-во вершин глаза
	for (int pointNo = 0; pointNo < Points; ++pointNo)
	{
		float angle = float(2 * M_PI * pointNo) / float(Points);	 //угол точки для элипса
		sf::Vector2f point = sf::Vector2f{							 //позиция точки
			size.x * std::cos(angle),  //позиция по x
			size.y * std::sin(angle)}; //позиция по y
		this->eyeApple.setPoint(pointNo, point);//установка точки
	}
	this->eyePupil.setRadius(RadiusPupil);
	this->eyePupil.setOrigin(RadiusPupil, RadiusPupil);									  
	this->eyePupil.setPosition(position);
	this->eyeApple.setFillColor(ColorApple);
	this->eyePupil.setFillColor(ColorPupil);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition) //функция получения/сохранения координат мыши
{
	mousePosition = {float(event.x), float(event.y)}; //
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition) //основной цикл программы
{
	sf::Event event;
	while (window.pollEvent(event))
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

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
							"These EYES see your cursor",
							sf::Style::Default,
							settings);
	sf::Vector2f mousePosition;

	Eye eyeLeft;
	Eye eyeRight;
	eyeLeft.init(sf::Vector2f({WINDOW_WIDTH/2 - (WidthEye+(DistanceBetweenEye/2)), WINDOW_HEIGHT/2}),sf::Vector2f({WidthEye, HeightEye}));
	eyeRight.init(sf::Vector2f({WINDOW_WIDTH/2 + (WidthEye+(DistanceBetweenEye/2)), WINDOW_HEIGHT/2}),sf::Vector2f({WidthEye, HeightEye}));
	
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		eyeLeft.update(mousePosition);
		eyeRight.update(mousePosition);
		window.clear();
		eyeLeft.draw(window);
		eyeRight.draw(window);
		window.display();
	}
}