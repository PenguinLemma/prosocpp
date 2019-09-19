#include <iostream>

int main()
{
    int number_of_chars;
    std::cin >> number_of_chars;
    int number_of_ones = 0;
    int number_of_zeros = 0;
    for (int i = 0; i < number_of_chars; ++i)
    {
        char c;
        std::cin >> c;
        if (c == 'z') ++number_of_zeros;
        else if (c == 'n') ++number_of_ones;
    }

    for (int i = 0; i < number_of_ones - 1; ++i)
    {
        std::cout << "1 ";
    }
    if (number_of_ones > 0)
    {
        std::cout << "1";
        if (number_of_zeros > 0)
            std::cout << " ";
    }
    for (int i = 0; i < number_of_zeros - 1; ++i)
    {
        std::cout << "0 ";
    }
    if (number_of_zeros > 0)
        std::cout << "0";
    
    std::cout << std::endl;
}