#include "../ConstantlyUsed.cpp"

constexpr float multiplex = 1;
constexpr float fileName = 50;
constexpr float maxSpeed = 50;
constexpr float maxSpeedLaser = 500;
const sf::Color BGColor = sf::Color({255, 255, 255});
const sf::String windowHeader = "KISIK :3";

bool CMP(float x1, float y1, float x2, float y2)
{
    if (std::abs(x2) - std::abs(x1) <= 0)
    {
        if (std::abs(y2) - std::abs(y1) <= 0)
        {
            return true;
        }
    }
}

struct CAT
{
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;

    int init(sf::String filename, sf::Vector2f position);
    int update(sf::Vector2f toPosition, float time);
    void draw(sf::RenderWindow &window);
private:
    void toMove(sf::Vector2f mousePosition);
};

struct Lazer
{
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    
    int init(sf::String filename, sf::Vector2f mousePosition);
    void update(sf::Vector2f toPosition, float time);
    sf::Vector2f getPos();
    void draw(sf::RenderWindow &window);
};

sf::Vector2f Lazer::getPos()
{
    return this->sprite.getPosition();
}

int Lazer::init(sf::String filename, sf::Vector2f position)
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
    this->speed = maxSpeedLaser;
    return 0;
}

void Lazer::update(sf::Vector2f toPosition, float time)
{
    sf::Vector2f delta = toPosition - this->sprite.getPosition();
    float angle = std::atan2(delta.y, delta.x);
    float x = this->speed * std::cos(angle) * time;
    float y = this->speed * std::sin(angle) * time;
    sf::Vector2f newPos = sf::Vector2f({x, y})+sprite.getPosition();

    if (CMP(x, y, delta.x, delta.y))
    {
        this->speed = 0;
        newPos = toPosition;
    }
    else
    {
        this->speed = maxSpeedLaser;
    }
    sprite.setPosition(newPos);
}

void Lazer::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

void CAT::toMove(sf::Vector2f toPosition)
{
    if(toPosition.x > 0)
    {
        this->sprite.setScale(multiplex, multiplex);
    }
    else if (toPosition.x < 0)
    {
        this->sprite.setScale(-multiplex, multiplex);
    }
}

int CAT::update(sf::Vector2f toPosition, float time)
{
    sf::Vector2f delta = toPosition - this->sprite.getPosition();
    float angle = std::atan2(delta.y, delta.x);
    toMove(delta);
    float x = this->speed * std::cos(angle) * time;
    float y = this->speed * std::sin(angle) * time;
    sf::Vector2f newPos = sf::Vector2f({x, y})+sprite.getPosition();

    if (CMP(x, y, delta.x, delta.y))
    {
        this->speed = 0;
        newPos = toPosition;
    }
    else
    {
        this->speed = maxSpeed;
    }
    sprite.setPosition(newPos);
}

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
    return 0;
}

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
		case sf::Event::MouseButtonPressed:						  //если пользователь двинул мышь
			onMouseClick(event.mouseButton, mousePosition); //сохраняем координаты
			break;
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
    sf::Vector2f mousePosition;
    CAT cat;
    Lazer lazer;
    if (1 == cat.init("cat.png", sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}))
    {
        std::cout << "No file load cat" << std::endl;
        return 1;
    }
    if (1 == lazer.init("lazer.png", sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}))
    {
        std::cout << "No file load lazer" << std::endl;
        return 1;
    }
    sf::Clock clock;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        const float time = clock.restart().asSeconds();
		lazer.update(mousePosition, time);
        window.clear(BGColor);
        cat.update(lazer.getPos(), time);
        lazer.draw(window);
        cat.draw(window);
        window.display();
    }
}