#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <string>
#include <utility>

std::string IntToString(int value) {
    if (value == 0) {
        return "0";
    }
    std::string s;
    bool is_positive = true;
    if (value < 0) {
        value = -1 * value;
        is_positive = false;
    }
    while (value > 0) {
        s += static_cast<char>('0' + value % 10);
        value /= 10;
    }
    
    if (!is_positive) {
        s += '-';
    }
    return {std::rbegin(s), std::rend(s)};
}

int StringToInt(std::string const& s)
{
    auto start = std::cbegin(s);
    int sign = 1;
    if (s[0] == '-') {
        sign = -1;
        ++start;
    }
    return sign *
           std::accumulate(start, std::cend(s), 0, [](auto current_value, auto digit_as_char) {
               return current_value * 10 + static_cast<int>(digit_as_char - '0');
           });
}

TEST_CASE("test1", "[5_6][IntToString][StringToInt]")
{

    auto const int_string = GENERATE(as<std::pair<int, std::string> >{},
                                     std::make_pair(298, "298"),
                                     std::make_pair(0, "0"),
                                     std::make_pair(-5123, "-5123"),
                                     std::make_pair(-99999999, "-99999999"),
                                     std::make_pair(-2, "-2"));
    REQUIRE(IntToString(int_string.first) == int_string.second);
    REQUIRE(StringToInt(int_string.second) == int_string.first);
}
