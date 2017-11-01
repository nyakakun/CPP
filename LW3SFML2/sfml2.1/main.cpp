#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

#define sizeShape 40
#define sizeFormX 800
#define sizeFormY 600

int main()
{

    sf::RenderWindow window(sf::VideoMode({sizeFormX, sizeFormY}), "Simple Event Mode");

    sf::Clock clock;

    float speedX = 100.f;
    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;
    float timePrevious = 0;
    float x = 0;

    //sf::Vector2f speed = {1000.f, 300.f};

    sf::CircleShape shape(sizeShape);
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Vector2f position = {10, 350};

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

        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        x += speedX * (time - timePrevious);
        timePrevious = time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        if ((position.x + x + 2 * sizeShape >= sizeFormX) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x + x <= 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        shape.setPosition(position + offset);

        window.clear();
        window.draw(shape);
        window.display();
    }
}