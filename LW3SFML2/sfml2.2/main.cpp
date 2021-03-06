#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <fstream>

int main()
{
    constexpr int pointCount = 200;

    constexpr float amplitude = 80.f;
    constexpr float period = 2;
    const sf::Vector2f position = {400, 300};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Ellipse",
        sf::Style::Default, settings);

    sf::Clock clock;

    sf::ConvexShape ellipse;
    ellipse.setPosition(position);
    ellipse.setFillColor(sf::Color(255, 255, 255));
    ellipse.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        const float radius = 200 * std::sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{
            radius * std::sin(angle),
            radius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

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
        const float wavePhase = clock.getElapsedTime().asSeconds() * float(2 * M_PI);
        const float y = amplitude * std::sin(wavePhase / period);
        const float x = amplitude * std::cos(wavePhase / period);
        const sf::Vector2f offset = {x,y};

        ellipse.setPosition(position + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}