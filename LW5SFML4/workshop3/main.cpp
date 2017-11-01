#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr float multiplex = 1;
constexpr float fileName = 50;
const sf::Color BGColor = sf::Color({255, 255, 255});
const sf::String windowHeader = "KISIK :3";
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct CAT
{
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f size;

    int init(sf::String filename, sf::Vector2f position);
    void draw(sf::RenderWindow &window);
};

void CAT::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

int CAT::init(sf::String filename, sf::Vector2f position)
{
    if(!this->texture.loadFromFile(filename))
    {
        return 1;
    }
    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(multiplex, multiplex);
    this->sprite.setOrigin(this->texture.getSize().x/2, this->texture.getSize().y/2);
    this->sprite.setPosition(position);
}

void pollEvents(sf::RenderWindow &window/*, sf::Vector2f &mousePosition*/) //основной цикл программы
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		//case sf::Event::MouseMoved:						 //если пользователь двинул мышь
			//onMouseMove(event.mouseMove, mousePosition); //сохраняем координаты
			//break;
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
                            windowHeader,
                            sf::Style::Default,
                            settings);
    //sf::Vector2f mousePosition;
    CAT cat;
    if (1 == cat.init("/home/cssource/AllLW/LWCPP/CPP/LW5SFML4/cat.png", sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}))
    {
        std::cout << "No file load" << std::endl;
        return 1;
    }
    sf::Clock clock;

    while (window.isOpen())
    {
		pollEvents(window/*, mousePosition*/);
        window.clear(BGColor);
        //cat.update(mousePosition, clock.restart().asSeconds());
        cat.draw(window);
        window.display();
    }
}