#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define marginRootShape 10  /*Отступ от края формы до края основы светофора*/
#define paddingRootShape 10 /*Отступ от края основы светофора до его элементов*/
#define radiusLight 100     /*Радиус элементов светофора*/

int main()
{
    /* Основа светофора*/
    sf::RectangleShape rootShape;
    rootShape.setPosition({marginRootShape, marginRootShape});
    rootShape.setSize({radiusLight * 2 + paddingRootShape * 2,
                       radiusLight * 6 + paddingRootShape * 4});
    rootShape.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));

    /* Зелёный свет*/
    sf::CircleShape lightGreen(radiusLight);
    lightGreen.setPosition({rootShape.getPosition().x + paddingRootShape,
                            rootShape.getPosition().y + paddingRootShape});
    lightGreen.setFillColor(sf::Color(0x0, 0xFF, 0x0));

    /* Жёлтый свет*/
    sf::CircleShape lightYellow(radiusLight);
    lightYellow.setPosition({rootShape.getPosition().x + paddingRootShape,
                             rootShape.getPosition().y + paddingRootShape * 2 + radiusLight * 2});
    lightYellow.setFillColor(sf::Color(0xFF, 0xFF, 0x0));

    /* Красный свет*/
    sf::CircleShape lightRed(radiusLight);
    lightRed.setPosition({rootShape.getPosition().x + paddingRootShape,
                          rootShape.getPosition().y + paddingRootShape * 3 + radiusLight * 4});
    lightRed.setFillColor(sf::Color(0xFF, 0x00, 0x0));

    sf::RenderWindow window(sf::VideoMode({rootShape.getSize().x + marginRootShape * 2,
                                           rootShape.getSize().y + marginRootShape * 2}),
                            "TRAFFIC LIGHT");

    window.clear();

    window.draw(rootShape);
    window.draw(lightGreen);
    window.draw(lightYellow);
    window.draw(lightRed);

    window.display();

    sf::sleep(sf::seconds(5));
}