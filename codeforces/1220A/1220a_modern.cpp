#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    int number_of_chars;
    std::cin >> number_of_chars;
    std::string s;
    std::cin >> s;
    int number_of_ones = std::count(std::begin(s), std::end(s), 'n');
    int number_of_zeros =  std::count(std::begin(s), std::end(s), 'z');
    
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