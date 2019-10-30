#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

double MaxProfitSingleBuyAndSell(std::vector<double> const& prices)
{
    if (prices.empty())
        return 0.0;

    double min_up_to_now = prices[0];
    double max_profit = 0.0;
    for (std::size_t i = 0; i < prices.size(); ++i) {
        if (prices[i] < min_up_to_now)
            min_up_to_now = prices[i];
        else if (prices[i] - min_up_to_now > max_profit)
            max_profit = prices[i] - min_up_to_now;
    }
    return max_profit;
}

double BruteForceSolution(std::vector<double> const& prices)
{
    if (prices.empty())
        return 0.0;
    double max_profit = 0.0;
    for (std::size_t i = 0; i < prices.size(); ++i) {
        for (std::size_t j = i + 1; j < prices.size(); ++j) {
            double profit = prices[j] - prices[i];
            if (profit > max_profit)
                max_profit = profit;
        }
    }
    return max_profit;
}

TEST_CASE("brute_force_tester", "[testers]")
{
    auto const in_out =
        GENERATE(as<std::pair<std::vector<double>, double> >{},
                 std::make_pair(std::vector<double>{}, 0.0),
                 std::make_pair(std::vector<double>{1.0, 2.0, 2.0}, 1.0),
                 std::make_pair(std::vector<double>{10.0, 5.1, 1.0, 7.5, 4.3, 0.2, 0.3, 0.8}, 6.5),
                 std::make_pair(std::vector<double>{4.0, 3.1, 3.0, 7.5, 4.3, 0.2, 5.3, 0.8}, 5.1));
    REQUIRE(BruteForceSolution(in_out.first) == in_out.second);
}

TEST_CASE("test1", "[5_6][BuyAndSellStockOnce]")
{

    auto const input =
        GENERATE(std::vector<double>{},
                 std::vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 1},
                 std::vector<double>{18.4, 99.6, 121.2, 5.2, 100.0, 1.2, 60.3, 79.4, 88.1},
                 std::vector<double>{6.2, 8.4, 21.4, 1.2, 12.9, 18.6, 0.5, 17.8, 11.1},
                 std::vector<double>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                 std::vector<double>{55.2, 23.8, 198.6, 204.1, 126.9, 163.7, 244.3, 11.4, 200.6, 
                                     176.2, 198.5, 221.6, 152.3, 1.2, 1.3, 12.6, 177.6});
    REQUIRE(MaxProfitSingleBuyAndSell(input) == BruteForceSolution(input));
}
