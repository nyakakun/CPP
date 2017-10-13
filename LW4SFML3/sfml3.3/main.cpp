#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr float WidthEye = 70;			 //�ਭ� �����
constexpr float HeightEye = 50;			 //���� �����
constexpr float RadiusPupil = 15;		 //������ ��箪
constexpr float DistBetEyeAndPupil = 10; //���⠭�� �� ��� ����� �� ��� ��窠
constexpr float DistanceBetweenEye = 50; //���⠭�� ����� �������dsfsfsdfsdf
constexpr float Points = 900;			 //���-�� �祪 ���
constexpr unsigned WINDOW_WIDTH = 800;   //�ਭ� ����
constexpr unsigned WINDOW_HEIGHT = 600;  //���� ����

struct Eye //������ �����
{
	sf::ConvexShape eyeApple;											   //"������� ���"
	sf::CircleShape eyePupil;											   //"��箪"
	sf::Vector2f position;												   //������ �����
	void init(float RadiusPupil, sf::Vector2f position, sf::Vector2f size) //���樠������ �����
	{
		eyeApple.setPosition(position); //������ "�������� ���"
		this->position = position;		//��⠭���� ����樨 �����, �⮡� ����� ����� 祣� �������
		eyeApple.setPointCount(Points); //���-�� ���設 �����

		for (int pointNo = 0; pointNo < Points; ++pointNo)
		{
			float angle = float(2 * M_PI * pointNo) / float(Points);	 //㣮� �窨 ��� ���
			sf::Vector2f point = sf::Vector2f{							 //������ �窨
											  size.y * std::sin(angle),  //������ �� y
											  size.x * std::cos(angle)}; //������ �� x
			eyeApple.setPoint(pointNo, point);							 //��⠭���� �窨
		}
		eyePupil.setRadius(RadiusPupil);														  //������ ࠤ��� ��窠
		eyePupil.setPosition(sf::Vector2f({position.x - RadiusPupil, position.y - RadiusPupil})); //������ ������ ��窠
		eyeApple.setFillColor(sf::Color(0xFF, 0x0, 0x0));										  //梥� ���
		eyePupil.setFillColor(sf::Color(0x0, 0x0, 0x0));										  //梥� ��窠
	};

	void update(sf::Vector2f &mousePosition) //�㭪�� ���������� ����樨 ���
	{
		const sf::Vector2f delta = mousePosition - position; //������ ����� �⭮�⥫쭮 業�� �����
		const float angle = atan2(delta.x, delta.y);		 //㣮� ����� �⭮�⥫쭮 業�� �����

		float Sin1 = (/*YOffset - */ HeightEye + (RadiusPupil + DistBetEyeAndPupil)) * std::sin(angle);
		float Sin2 = (/*YOffset - */ HeightEye + (RadiusPupil + DistBetEyeAndPupil)) * std::sin(angle - M_PI);
		float Cos1 = (/*XOffset - */ WidthEye + (RadiusPupil + DistBetEyeAndPupil)) * std::cos(angle);
		float Cos2 = (/*XOffset - */ WidthEye + (RadiusPupil + DistBetEyeAndPupil)) * std::cos(angle - M_PI);

		/*float YOffset = 0;
		float YOffset = 0;*/
		int flag = 1;
		if ((delta.y <= std::max(Sin1, Sin2)) && (delta.y >= std::min(Sin1, Sin2)))
		{
			if ((delta.x <= std::max(Cos1, Cos2)) && (delta.x >= std::min(Cos1, Cos2)))
			{
				eyePupil.setPosition(mousePosition - sf::Vector2f({RadiusPupil, RadiusPupil}));
				flag = 0;
				std::cout << "����᪢�� �����" << std::endl;
			}
		}
		if (flag == 1)
		{
			const sf::Vector2f offsetPupil = {																					 //ᬥ饭�� ��窠 �⭮�⥫쭮 業�� �����
											  (/*YOffset - */ HeightEye - (RadiusPupil + DistBetEyeAndPupil)) * std::sin(angle), //ᬥ饭�� �� y
											  (/*XOffset - */ WidthEye - (RadiusPupil + DistBetEyeAndPupil)) * std::cos(angle)}; //ᬥ饭�� �� �
			eyePupil.setPosition((position - sf::Vector2f({RadiusPupil, RadiusPupil})) + offsetPupil);							 //������ ��窠
		}
	};

	void draw(sf::RenderWindow &window) //�㭪�� ���ᮢ�� �����
	{
		window.draw(eyeApple); //
		window.draw(eyePupil); //
	}
};

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition) //�㭪�� ����祭��/��࠭���� ���न��� ���
{
	mousePosition = {float(event.x), float(event.y)}; //
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition) //�᭮���� 横� �ணࠬ��
{
	sf::Event event;
	while (window.pollEvent(event)) //
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:						 //�᫨ ���짮��⥫� ����� ����
			onMouseMove(event.mouseMove, mousePosition); //��࠭塞 ���न����
			break;
		default:
			break;
		}
	}
}

int main() //
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
							"These EYES see your cursor",
							sf::Style::Default,
							settings);
	sf::Vector2f mousePosition;

	Eye leftEye;  //���� ����
	Eye RightEye; //�ࠢ� ����

	float XLeft = (WINDOW_WIDTH / 2) - WidthEye - (DistanceBetweenEye / 2);  //� ������ ������ �����
	float XRight = (WINDOW_WIDTH / 2) + WidthEye + (DistanceBetweenEye / 2); //� ������ �ࠢ��� �����

	float YLeft = (WINDOW_HEIGHT / 2) - HeightEye;  //� ������ ������ �����
	float YRight = (WINDOW_HEIGHT / 2) - HeightEye; //� ������ �ࠢ��� �����

	leftEye.init(RadiusPupil, sf::Vector2f({XLeft, YLeft}), sf::Vector2f({WidthEye, HeightEye}));	//���樠������ ������ �����
	RightEye.init(RadiusPupil, sf::Vector2f({XRight, YRight}), sf::Vector2f({WidthEye, HeightEye})); //���樠������ �ࠢ�� �����
	while (window.isOpen())																			 //
	{
		pollEvents(window, mousePosition);
		leftEye.update(mousePosition);  //������塞 ���� ����
		RightEye.update(mousePosition); //������塞 �ࠢ�
		window.clear();
		leftEye.draw(window);  //���᮪� ������
		RightEye.draw(window); //���ᮢ�� �ࠢ��� �����
		window.display();
	}
}