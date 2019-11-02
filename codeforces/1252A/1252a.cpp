#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::size_t permutation_size;
    std::cin >> permutation_size;
    std::vector<int> perm(permutation_size);
    for (std::size_t i = 0; i < permutation_size; ++i) {
        std::cin >> perm[i];
    }
    std::transform(std::begin(perm), std::end(perm), std::begin(perm), [=](auto a) {
        return permutation_size - a + 1;
    });
    for (std::size_t i = 0; i < permutation_size - 1; ++i)
    {
        std::cout << perm[i] << " ";
    }
    std::cout << perm[permutation_size - 1] << std::endl;
}