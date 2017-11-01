#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float multiplex = 70;
constexpr float border = 5;

struct Arrow
{
    sf::ConvexShape arrow;
    //sf::Vector2f position;
    //float rotation;

    void initialization(sf::Vector2f position);
    /*void update(sf::Vector2f &mousePosition);*/
    void draw(sf::RenderWindow &window);
private:
    const float WA = 3;
    const float HA = 4;
    const float GA = 0.5;
    const float HHA = 1;
};

void Arrow::draw(sf::RenderWindow &window)
{
    window.draw(this->arrow);
}

void Arrow::initialization(sf::Vector2f position)
{
    this->arrow.setPosition(position);
    
    this->arrow.setPointCount(7);
        
    this->arrow.setFillColor(sf::Color::Yellow);

    this->arrow.setOutlineThickness(border);
    this->arrow.setOutlineColor(sf::Color::Black);

    float HH = HA/2;
    float HW = WA/2;
    
    this->arrow.setPoint(0,sf::Vector2f({-(HW-GA)*multiplex,0}));
    this->arrow.setPoint(1,sf::Vector2f({-HW*multiplex,0}));
    this->arrow.setPoint(2,sf::Vector2f({0,-(HH)*multiplex}));
    this->arrow.setPoint(3,sf::Vector2f({HW*multiplex,0}));
    this->arrow.setPoint(4,sf::Vector2f({(HW-GA)*multiplex,0}));
    this->arrow.setPoint(5,sf::Vector2f({(HW-GA)*multiplex,(HH)*multiplex}));
    this->arrow.setPoint(6,sf::Vector2f({-(HW-GA)*multiplex,(HH)*multiplex}));
}

void pollEventsMove(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
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
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "ARROW", sf::Style::Default, settings);

    Arrow arrow;
    arrow.initialization(sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});

    while (window.isOpen())
    {
        pollEventsMove(window);
        window.clear(sf::Color::White);
        arrow.draw(window);
        window.display();
    }
}