#include <iostream>
#include <string>

int main()
{
    int num_airports, origin, destination;
    std::cin >> num_airports >> origin >> destination;
    std::string owners;
    std::cin >> owners;
    std::cout << !(owners[origin-1] == owners[destination-1])
                  << std::endl;
}
