#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using CountingMatrix = std::vector<std::vector<uint32_t> >;
using StepDecisionMatrix = std::vector<std::vector<char> >;

template <typename Matrix>
void WriteMatrix(Matrix const& m)
{
    int const size = static_cast<int>(m.size());
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size - 1; ++c) {
            std::cout << m[r][c] << " ";
        }
        std::cout << m[r][size - 1] << "\n";
    }
    std::cout << std::endl;
}

std::pair<uint32_t, uint32_t> Get2sAnd5s(uint32_t number)
{
    int twos = 0;
    while (number > 1 && number % 2 == 0) {
        number /= 2;
        ++twos;
    }
    int fives = 0;
    while (number > 1 && number % 5 == 0) {
        number /= 5;
        ++fives;
    }
    return {twos, fives};
}

std::string ComputePath(StepDecisionMatrix const& steps)
{
    std::string result{};

    int row = steps.size() - 1;
    int col = steps.size() - 1;

    while (row >= 0 && col >= 0 && (row != 0 || col != 0)) {
        result = result + steps[row][col];
        if (steps[row][col] == 'R')
            --col;
        else
            --row;
    }

    return {std::rbegin(result), std::rend(result)};
}

void MinimalPaths(CountingMatrix& twos,
                  CountingMatrix& fives,
                  StepDecisionMatrix& step_twos,
                  StepDecisionMatrix& step_fives)
{
    int const size(static_cast<int>(twos.size()));

    std::partial_sum(std::begin(twos[0]), std::end(twos[0]), std::begin(twos[0]));  // top row
    std::fill(std::begin(step_twos[0]), std::end(step_twos[0]), 'R');

    for (int row = 1; row < size; ++row) {
        twos[row][0] += twos[row - 1][0];  // partial_sum for first column
        step_twos[row][0] = 'D';
    }
    std::partial_sum(std::begin(fives[0]), std::end(fives[0]), std::begin(fives[0]));  // top row
    std::fill(std::begin(step_fives[0]), std::end(step_fives[0]), 'R');

    for (int row = 1; row < size; ++row) {
        fives[row][0] += fives[row - 1][0];  // partial_sum for first column
        step_fives[row][0] = 'D';
    }

    for (int row = 1; row < size; ++row) {
        for (int col = 1; col < size; ++col) {
            auto const twos_from_left = twos[row][col - 1];
            auto const fives_from_left = fives[row][col - 1];
            auto const twos_from_top = twos[row - 1][col];
            auto const fives_from_top = fives[row - 1][col];
            if (twos_from_left < twos_from_top) {
                twos[row][col] += twos_from_left;
                step_twos[row][col] = 'R';
            }
            else {
                twos[row][col] += twos_from_top;
                step_twos[row][col] = 'D';
            }

            if (fives_from_left < fives_from_top) {
                fives[row][col] += fives_from_left;
                step_fives[row][col] = 'R';
            }
            else {
                fives[row][col] += fives_from_top;
                step_fives[row][col] = 'D';
            }
        }
    }
}

std::string PathThroughZero(uint32_t row, uint32_t size)
{
    std::string result{};
    for (uint32_t r = 0; r < row; ++r)
        result = result + 'D';
    for (uint32_t c = 1; c < size; ++c)
        result = result + 'R';
    for (uint32_t r = row + 1; r < size; ++r)
        result = result + 'D';
    return result;
}

int main()
{
    uint32_t n;
    std::cin >> n;

    CountingMatrix twos(n, std::vector<uint32_t>(n));
    CountingMatrix fives(n, std::vector<uint32_t>(n));
    StepDecisionMatrix steps_twos(n, std::vector<char>(n));
    StepDecisionMatrix steps_fives(n, std::vector<char>(n));
    std::optional<std::pair<uint32_t, uint32_t> > zero(std::nullopt);
    for (uint32_t row = 0; row < n; ++row) {
        for (uint32_t col = 0; col < n; ++col) {
            int number;
            std::cin >> number;
            if (number == 0) {
                // we note there is a 0 and treat it as a 10
                zero = std::make_pair(row, col);
                twos[row][col] = 1;
                fives[row][col] = 1;
            }
            else {
                std::tie(twos[row][col], fives[row][col]) =
                    Get2sAnd5s(static_cast<uint32_t>(number));
            }
        }
    }

    MinimalPaths(twos, fives, steps_twos, steps_fives);

    if (zero && std::min(twos[n - 1][n - 1], fives[n - 1][n - 1]) > 1) {
        std::cout << "1\n" << PathThroughZero(zero.value().first, n) << std::endl;
    }
    else {
        std::cout << std::min(twos[n - 1][n - 1], fives[n - 1][n - 1]) << "\n"
                  << ComputePath(twos[n - 1][n - 1] < fives[n - 1][n - 1] ? steps_twos
                                                                          : steps_fives)
                  << std::endl;
    }
}
