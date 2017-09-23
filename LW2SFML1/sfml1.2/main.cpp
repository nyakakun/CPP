#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define size 20
#define top 10
#define colorAbbr 0xFF, 0xFF, 0xFF

int main()
{

    /*ЭТО БУКВА M*/

    sf::RectangleShape ShapeM1;
    sf::RectangleShape ShapeM2;
    sf::RectangleShape ShapeM3;
    sf::RectangleShape ShapeM4;

    ShapeM1.setPosition({10, top});
    ShapeM2.setPosition({30, top});
    ShapeM3.setPosition({143, top});
    ShapeM4.setPosition({143, top});

    ShapeM1.setSize({size, size * 7});
    ShapeM2.setSize({size, size * 5});
    ShapeM3.setSize({size, size * 5});
    ShapeM4.setSize({size, size * 7});

    ShapeM1.setFillColor(sf::Color(colorAbbr));
    ShapeM2.setFillColor(sf::Color(colorAbbr));
    ShapeM3.setFillColor(sf::Color(colorAbbr));
    ShapeM4.setFillColor(sf::Color(colorAbbr));

    ShapeM1.setRotation(0);
    ShapeM2.setOrigin(size, 0);
    ShapeM2.setRotation(-45);
    ShapeM3.setRotation(45);
    ShapeM4.setRotation(0);

    /*ЭТО КОНЕЦ БУКВЕ M*/

    /*ЭТО БУКВА V*/

    sf::RectangleShape ShapeV1;
    sf::RectangleShape ShapeV2;
    sf::RectangleShape ShapeV3;
    sf::RectangleShape ShapeV4;
    sf::RectangleShape ShapeV5;

    ShapeV1.setPosition({213, top});
    ShapeV2.setPosition({313, top});
    ShapeV3.setPosition({250, top + 120});
    ShapeV4.setPosition({194, top});
    ShapeV5.setPosition({313, top});

    ShapeV1.setSize({size, size * 7});
    ShapeV2.setSize({size, size * 7});
    ShapeV3.setSize({26, size});
    ShapeV4.setSize({19, 7});
    ShapeV5.setSize({19, 7});

    ShapeV1.setFillColor(sf::Color(colorAbbr));
    ShapeV2.setFillColor(sf::Color(colorAbbr));
    ShapeV3.setFillColor(sf::Color(colorAbbr));
    ShapeV4.setFillColor(sf::Color(colorAbbr));
    ShapeV5.setFillColor(sf::Color(colorAbbr));

    ShapeV1.setOrigin(size, 0);
    ShapeV1.setRotation(-23);
    ShapeV2.setRotation(23);
    ShapeV3.setRotation(0);
    ShapeV4.setRotation(0);
    ShapeV5.setRotation(0);

    /*ЭТО КОНЕЦ БУКВЕ V*/

    /*ЭТО БУКВА D*/

    sf::RectangleShape ShapeD1;
    sf::RectangleShape ShapeD2;
    sf::RectangleShape ShapeD3;
    sf::RectangleShape ShapeD4;
    sf::CircleShape ShapeD5(size);
    sf::CircleShape ShapeD6(size);
    sf::RectangleShape ShapeD7;

    ShapeD1.setPosition({363, top});
    ShapeD2.setPosition({363, top});
    ShapeD3.setPosition({363, top + 120});
    ShapeD4.setPosition({463, top + 20});
    ShapeD5.setPosition({443, top});
    ShapeD6.setPosition({443, top + 100});
    ShapeD7.setPosition({443, top + 20});

    ShapeD1.setSize({size, size * 7});
    ShapeD2.setSize({size * 5, size});
    ShapeD3.setSize({size * 5, size});
    ShapeD4.setSize({size, size * 5});
    ShapeD7.setSize({size, size * 5});

    ShapeD1.setFillColor(sf::Color(colorAbbr));
    ShapeD2.setFillColor(sf::Color(colorAbbr));
    ShapeD3.setFillColor(sf::Color(colorAbbr));
    ShapeD4.setFillColor(sf::Color(colorAbbr));
    ShapeD5.setFillColor(sf::Color(colorAbbr));
    ShapeD6.setFillColor(sf::Color(colorAbbr));
    ShapeD7.setFillColor(sf::Color(0x0, 0x0, 0x0));

    /*ЭТО КОНЕЦ БУКВЕ D*/

    sf::RenderWindow window(sf::VideoMode({493, 160}), "MY ABBR");

    window.clear();

    window.draw(ShapeM1);
    window.draw(ShapeM2);
    window.draw(ShapeM3);
    window.draw(ShapeM4);

    window.draw(ShapeV1);
    window.draw(ShapeV2);
    window.draw(ShapeV3);
    window.draw(ShapeV4);
    window.draw(ShapeV5);

    window.draw(ShapeD1);
    window.draw(ShapeD2);
    window.draw(ShapeD3);
    window.draw(ShapeD4);
    window.draw(ShapeD5);
    window.draw(ShapeD6);
    window.draw(ShapeD7);

    window.display();

    sf::sleep(sf::seconds(5));
}