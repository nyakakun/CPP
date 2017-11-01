#include "ball.cpp"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
const sf::Color BGColor = sf::Color({255, 255, 255});
const sf::String windowHeader = "KISIK :3";

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition) //основной цикл программы
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
//		case sf::Event::MouseButtonPressed:						  //если пользователь двинул мышь
//			onMouseClick(event.mouseButton, mousePosition); //сохраняем координаты
//			break;
		default:
			break;
		}
	}
}

int main()
{
    srand(unsigned(time(nullptr)));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            windowHeader,
                            sf::Style::Default,
                            settings);
    Vector4f frame;
    frame.setValue(20,20,WINDOW_WIDTH-20,WINDOW_HEIGHT-20);
    sf::Vector2f mousePosition;
    Ball cat;
    cat.init(sf::Vector2f(WINDOW_WIDTH/2,WINDOW_HEIGHT/2),sf::Color::Red, frame, 20);
    sf::Clock clock;

    while (window.isOpen())
    {
		pollEvents(window, mousePosition);
        window.clear(BGColor);
        cat.update(clock.restart().asSeconds());
        cat.draw(window);
        window.display();
    }
}