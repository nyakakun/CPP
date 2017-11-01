#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr float multiplex = 20;
constexpr float border = 5;
constexpr float maxSpeedMove = 100;
constexpr float maxSpeedRotate = 90;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

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

bool CMP(float x1, float y1, float x2, float y2)
{
    if (std::abs(x2) - std::abs(x1) <= 0)
    {
        if (std::abs(y2) - std::abs(y1) <= 0)
        {
            return true;
        }
        
    }
    
}

struct Arrow
{
    sf::ConvexShape arrow;

    void initialization(sf::Vector2f position);
    void update(sf::Vector2f &mousePosition, float time);
    void draw(sf::RenderWindow &window);
    float speedMove;
    float speedRotate;
  private:
    const float WA = 3;
    const float HA = 4;
    const float GA = 0.75;
    const float HHA = 1;
    float toRotate(float angleMouse, float angleArrow);
    sf::Vector2f toMove(float angleArrow, float time);
};

sf::Vector2f Arrow::toMove(float angleArrow, float time)
{

    float x = this->speedMove * std::cos(angleArrow) * time;
    float y = this->speedMove * std::sin(angleArrow) * time;

    return sf::Vector2f({x, y});
}

float Arrow::toRotate(float angleMouse, float angleArrow)
{
    float move = 1;
    if (angleMouse != angleArrow)
    {
        if(angleMouse < angleArrow)
        {
            if (180 > (angleArrow - angleMouse)) {move = -1;}
        }
        else
        {
            if (180 < (angleMouse - angleArrow)) {move = -1;}
        }
    }
    else
    {
        move = 0;
    }
    return speedRotate*move;
}

void Arrow::update(sf::Vector2f &mousePosition, float time)
{
    sf::Vector2f delta = mousePosition - this->arrow.getPosition();
    float angleMouse = convertAngle(toGrees(std::atan2(delta.y, delta.x)));
    float angleArrow = convertAngle(this->arrow.getRotation());
    float deltaRotate = time * toRotate(angleMouse, angleArrow);

    float toAngle = deltaRotate+this->arrow.getRotation();

    if(std::abs(deltaRotate) > (std::max(angleArrow,angleMouse)-std::min(angleMouse,angleArrow)))
    {
        toAngle = angleMouse;
    }

    sf::Vector2f deltaMove = toMove(toRadins(toAngle), time);
    sf::Vector2f newPosition = this->arrow.getPosition() + deltaMove;

    if (CMP(deltaMove.x, deltaMove.y, delta.x, delta.y))
    {
        this->speedMove = 0;
        this->speedRotate = 0;
        newPosition = mousePosition;
        toAngle = arrow.getRotation();
    }
    else
    {
        this->speedMove = maxSpeedRotate;
        this->speedRotate = maxSpeedMove;
    }

    arrow.setRotation(toAngle);
    arrow.setPosition(newPosition);
}

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

    this->speedMove = maxSpeedRotate;
    this->speedRotate = maxSpeedMove;
    
    this->arrow.setPoint(0,sf::Vector2f({0,-(HW-GA)*multiplex}));
    this->arrow.setPoint(1,sf::Vector2f({0,-HW*multiplex}));
    this->arrow.setPoint(2,sf::Vector2f({(HH)*multiplex,0}));
    this->arrow.setPoint(3,sf::Vector2f({0,HW*multiplex}));
    this->arrow.setPoint(4,sf::Vector2f({0,(HW-GA)*multiplex}));
    this->arrow.setPoint(5,sf::Vector2f({-(HH)*multiplex,(HW-GA)*multiplex}));
    this->arrow.setPoint(6,sf::Vector2f({-(HH)*multiplex,-(HW-GA)*multiplex}));
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
        case sf::Event::MouseLeft:
            mousePosition = sf::Vector2f({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
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
                            "STRELOCH`KA))000))",
                            sf::Style::Default,
                            settings);
    sf::Vector2f mousePosition;
    Arrow arrow;
    arrow.initialization(sf::Vector2f({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}));
    sf::Clock clock;

    while (window.isOpen())
    {
		pollEvents(window, mousePosition);
        window.clear(sf::Color::White);
        arrow.update(mousePosition, clock.restart().asSeconds());
        arrow.draw(window);
        window.display();
    }
}