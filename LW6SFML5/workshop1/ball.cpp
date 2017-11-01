#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>

float toGrees(float radians)
{
    return float(radians * (180 / M_PI) );
}

float toRadins(float grees)
{
    return float(grees * (M_PI / 180) );
}

const float BorderWidth = 5;

struct Vector4f
{
    float x1;
    float y1;
    float x2;
    float y2;
    void setValue(float x, float y, float w, float h);
};

void Vector4f::setValue(float x1, float y1, float x2, float y2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
};

struct Ball
{
    sf::CircleShape kernel;
    Vector4f movementFrame;
    float direction;
    float speed;

    void update(float time);
    //void updatePhantom(float time);
    void init(sf::Vector2f position, sf::Color color, Vector4f frame, float radius);
    void draw(sf::RenderWindow &window);
private:
    //sf::CircleShape phantom;
    void initialization(sf::CircleShape &ball, sf::Vector2f position, sf::Color color, float radius);
};

void Ball::initialization(sf::CircleShape &ball, sf::Vector2f position, sf::Color color, float radius)
{
    ball.setRadius(radius);
    ball.setOrigin(radius,radius);
    ball.setPosition(position);
    ball.setFillColor(color);
    ball.setOutlineThickness(BorderWidth);
    ball.setOutlineColor(sf::Color::Black);
}

void Ball::update(float time)
{
    float x = time * std::cos(this->direction) * this->speed;
    float y = time * std::sin(this->direction) * this->speed;
    if ((x < this->movementFrame.x1) || (x > this->movementFrame.x2))
    {
        this->direction = toRadins(180) - this->direction;
        
    }
    if ((y < movementFrame.y1) || (y > movementFrame.y2))
    {
        this->direction = (- this->direction);
    }
    std::cout << this->direction << " = direction" << std::endl;
    std::cout << this->direction << " = x" << std::endl << this->direction << " = x1" << std::endl << this->direction << " = x2" << std::endl;
    std::cout << this->direction << " = y" << std::endl << this->direction << " = y1" << std::endl << this->direction << " = y2" << std::endl;
    sf::Vector2f offset = sf::Vector2f({x,y});
    this->kernel.setPosition(this->kernel.getPosition()+offset);
}

//void updatePhantom(float time)
//{

//}

void Ball::init(sf::Vector2f position, sf::Color color, Vector4f frame, float radius)
{
    this->initialization(kernel, position, color, radius);
    //this->initialization(phantom, position, color, radius);
    this->direction = toRadins(45);
    std::cout << this->direction << " = direction" << std::endl;
    this->speed =  100 + rand() % 50;
    this->movementFrame = frame;
}

void Ball::draw(sf::RenderWindow &window)
{
    window.draw(this->kernel);
}