#include <cstdio>

int main()
{
    float a = 0;
    float b = 0;
    float x = 0;
    //Показать пользователю куда он попал и что нужно сделать
    std::puts("This program calculates x from formula ax+b=0\nPlease, write b:");
    //Считываем b и просим ввести a
    std::scanf("%f", &b);
    std::puts("Please, write a:");
    //Считываем a
    std::scanf("%f", &a);
    //Расчитываем x
    x = (-b) / a;
    std::printf("Solution: x = %f", x);
}