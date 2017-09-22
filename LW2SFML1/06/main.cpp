#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define offsetX 100
#define offsetY 10

int main()
{
    sf::ConvexShape roof;
    roof.setPosition({offsetX, 100 + offsetY});
    roof.setPointCount(4);
    roof.setPoint(0, {100, 0});
    roof.setPoint(1, {400, 0});
    roof.setPoint(2, {500, 100});
    roof.setPoint(3, {0, 100});
    roof.setFillColor(sf::Color(0x6A, 0x35, 0x35));

    sf::RectangleShape wall;
    wall.setPosition({50 + offsetX, 200 + offsetY});
    wall.setSize({400, 200});
    wall.setFillColor(sf::Color(0x6C, 0x1E, 0x00));

    sf::RectangleShape door;
    door.setPosition({100 + offsetX, 250 + offsetY});
    door.setSize({100, 150});
    door.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));

    sf::RectangleShape pipe1;
    pipe1.setPosition({offsetX + 300, offsetY + 50});
    pipe1.setSize({100, 40});
    pipe1.setFillColor(sf::Color(0x5F, 0x5F, 0x5F));

    sf::RectangleShape pipe2;
    pipe2.setPosition({offsetX + 325, offsetY + 90});
    pipe2.setSize({50, 60});
    pipe2.setFillColor(sf::Color(0x5F, 0x5F, 0x5F));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Convex Shapes");

    window.clear();

    window.draw(roof);
    window.draw(wall);
    window.draw(door);
    window.draw(pipe1);
    window.draw(pipe2);

    window.display();

    sf::sleep(sf::seconds(5));
}