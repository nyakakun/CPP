#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define sizeShape 40
#define sizeFormX 800
#define sizeFormY 600

int main()
{
    sf::RenderWindow window(sf::VideoMode({sizeFormX, sizeFormY}), "Simple Event Mode");

    sf::Clock clock;

    sf::Vector2f speed = {1000.f, 300.f};

    sf::CircleShape shape(sizeShape);
    shape.setPosition({200, 120});
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Vector2f position = shape.getPosition();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();
        position += speed * deltaTime;

        if ((position.x + 2 * sizeShape >= sizeFormX) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * sizeShape >= sizeFormY) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }

        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }
}