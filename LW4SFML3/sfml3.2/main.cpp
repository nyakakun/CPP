#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr float WidthEye = 0;
constexpr float HeightEye = 0;
constexpr float RadiusPupil = 0;
constexpr float DistanceBetweenEye = 0;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct Eye
{
	sf::ConvexShape eyeApple;
	sf::CircleShape eyePupil;
	sf::Vector2f position;
	float rotation;
	void update();	
	void init(float RadiusPupil);
}

void
init(sf::ConvexShape &pointer, float posX, float posY)
{
	pointer.setPointCount(3);
	pointer.setPoint(0, {40, 0});
	pointer.setPoint(1, {-20, -20});
	pointer.setPoint(2, {-20, 20});
	pointer.setPoint(2, {-20, 20});
	pointer.setPosition({400, 300});
	pointer.setFillColor(sf::Color(0xFF, 0x80, 0x0));
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			onMouseMove(event.mouseMove, mousePosition);
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
							"This EYES see your cursor",
							sf::Style::Default,
							settings);
	sf::ConvexShape pointer;
	sf::Vector2f mousePosition;

	init(pointer);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, pointer, clock.restart().asSeconds(), speed);
		//redrawFrame(window, pointer);
	}
}