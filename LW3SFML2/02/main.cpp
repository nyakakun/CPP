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

        constexpr float speedX = 100.f;
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float x = speedX * time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        shape.setPosition(position + offset);

        window.clear();
        window.draw(shape);
        window.display();
    }
}