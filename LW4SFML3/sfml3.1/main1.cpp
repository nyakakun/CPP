#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace std; // это нужно чтобы не писать постоянно std::cout... и т.д.
using namespace sf;  // та же история только sf. тоесть мы явно указывает что будем использовать это пространство имён..

const float maxAngularSpeed = 15; // максимальная скорость

//перевод радиан в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI); //перевод радиан в градусы
}

// обраб событие mouseMove обнов поз мыши
void onMouseMove(const Event::MouseMoveEvent &event, Vector2f &mousePosition)
{
    cout << "mouse x=" << event.x << ", y=" << event.y << endl; // то что по сути нам вообще не нужно, вывод в консоли координат мыши

    mousePosition = {float(event.x), float(event.y)}; // звпоминаем позицию мыши
}
void init(ConvexShape &pointer) // инициализация стрелочки..
{
    pointer.setPointCount(3);         // количество вершин выпуклого многоугольника
    pointer.setPoint(0, {40, 0});     // позиция первой вершины
    pointer.setPoint(1, {-20, -20});  // вы не поверите.... но это позиция второй вершины
    pointer.setPoint(2, {-20, 20});   // третьей...
    pointer.setPosition({400, 300});  // позиция стрелочки на форме приложения
    pointer.setFillColor(Color::Red); // цвет стрелочки))0))
}

void redrawFrame(RenderWindow &window, ConvexShape &pointer) // я думаю что это не требует объяснений
{
    window.clear();
    window.draw(pointer);
    window.display();
}
void pollEvents(RenderWindow &window, Vector2f &mousePosition)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}
//обновляем фигуру указ на мышь
void update(const Vector2f mousePosition, ConvexShape &pointer, float time) //самое интересное, вращение стрелочки за указателем
{
    const Vector2f delta = mousePosition - pointer.getPosition(); //находим позицию мыши относительно координат стрелчки
    float angle = toDegrees(atan2(delta.y, delta.x));             //выясняем на каком углу находится курсор мыши
    float DeltaAngle = maxAngularSpeed * time;                    //выясняем на сколько градусов мы сдвинулись со времени прошедшего кадра
    float toMove = 1;                                             // предполагаем что мы будем двигаться по часовой стрелке
    if (angle < 0)                                                // после тангенса углы идут от 0 до 180 и от -180 до 0 здесь мы это поправляем
                                                                  // чтобы угол до которого нужно повернуться всегда был положительным
    {
        angle = 360 + angle;
    }

    if (angle < pointer.getRotation()) // если угол до которогонужно повернуться меньше чем угол на который повёрнута стрелка то...
    {
        if (pointer.getRotation() - angle < 180) // если угол на который повёрнута стрелка минус угол на который нужно повернуться меньше 180 градусов то нам надо двигаться против часовой стрелки ибо так быстрее
        {
            toMove = -1;
        }
        else if (pointer.getRotation() - angle < DeltaAngle) // если угол на который осталось довернуться меньше угла на который поворачиваемся за кадр то двигаться больше не надо
        {
            toMove = 0;
        }
    }
    else if (angle > pointer.getRotation()) // иначе если угол до которого нужно повернуться больше чем угол на который стрелка уже повёрнута то...
    {
        if (angle - pointer.getRotation() > 180) // если угол на который нужно повернуться минус угол на который повёрнута стрелка меньше 180 градусов то нам надо двигаться против часовой стрелки ибо так быстрее
        {
            toMove = -1;
        }
        else if (pointer.getRotation() - angle < DeltaAngle) // если угол на который осталось довернуться меньше угла на который поворачиваемся за кадр то двигаться больше не надо
        {
            toMove = 0;
        }
    }
    else if (angle == pointer.getRotation()) // если углы равны то ни куда не нужно крутиться... мы тут не спинеры чтоб просто так крутиться
    {
        toMove = 0;
    }

    if (toMove = 0) // если двигаться не надо то просто сразу указываем на мышь
    {
        pointer.setRotation(angle);
    }
    else
    {
        pointer.setRotation(pointer.getRotation() + DeltaAngle * toMove); // иначе крутим стрелочку (спинеры повсюду)
    }

    cout << angle << "angle" << endl;
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "FOLLOW", Style::Default, settings);

    Clock clock;

    ConvexShape pointer;
    Vector2f mousePosition;

    init(pointer);

    while (window.isOpen())
    {

        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock.restart().asSeconds());
        redrawFrame(window, pointer);
    }
}
