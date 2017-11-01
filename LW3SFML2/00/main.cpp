#include <iostream>

int main()
{
    for (int num = 1; num <= 100; num++)
    {
        if ((num % 3 == 0) && (num % 5 == 0))
        {
            std::cout << "FizzBuss" << std::endl;
        }
        else if (num % 3 == 0)
        {
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 3 == 0)
        {
            std::cout << "Buss" << std::endl;
        }
        else
        {
            std::cout << num << std::endl;
        }
    }
}