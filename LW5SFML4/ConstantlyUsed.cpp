#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

float convertAngle(float angle);
float toGrees(float radians);
float toRadins(float Grees);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
sf::Vector2f calcDeltaMove(float speedX, float speedY, float angle);
void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition);

sf::Vector2f calcDeltaMove(float speedX, float speedY, float angle)
{
	return sf::Vector2f{
		speedX * std::cos(angle),
		speedY * std::cos(angle)
	};
}

float convertAngle(float angle)
{
    if (angle < 0)
    {
        return angle + 360;
    } 
    else 
    {
        return angle;
    };
}

float toGrees(float radians) 
{
    return float(double(radians) * 180.0 / M_PI);
}

float toRadins(float Grees) 
{
    return float(double(Grees* M_PI) / 180.0 );
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    if(event.button == sf::Mouse::Left)
    {
        mousePosition = {float(event.x), float(event.y)};
    }
}