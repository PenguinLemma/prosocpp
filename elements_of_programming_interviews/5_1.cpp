#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

void DutchFlagPartition(std::vector<int>& v, int pivot_index)
{
    if (v.empty())
        return;

    int pivot = v[pivot_index];
    int index_processed_head = 0;
    int index_processed_tail = static_cast<int>(v.size()) - 1;
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        if (v[i] < pivot) {
            std::swap(v[i], v[index_processed_head]);
            ++index_processed_head;
        }
    }
    for (int i = static_cast<int>(v.size()) - 1; i >= index_processed_head; --i) {
        if (v[i] > pivot) {
            std::swap(v[i], v[index_processed_tail]);
            --index_processed_tail;
        }
    }
}

// TODO: rewrite this using iterators and algorithm instead of int i
bool IsDutchFlagPartitioned(std::vector<int> const& v, int pivot)
{
    if (v.empty())
        return true;

    auto const first_not_smaller =
        std::find_if_not(std::cbegin(v), std::cend(v), [=](auto value) { return value < pivot; });
    auto const first_not_equal_after_smaller = std::find_if_not(
        first_not_smaller, std::cend(v), [=](auto value) { return value == pivot; });

    if (first_not_equal_after_smaller != std::cend(v) && *first_not_equal_after_smaller < pivot)
        return false;

    auto const first_not_bigger_after_smaller_and_equal = std::find_if_not(
        first_not_equal_after_smaller, std::cend(v), [=](auto value) { return value > pivot; });

    return first_not_bigger_after_smaller_and_equal == std::cend(v);
}

bool SameElements(std::vector<int> const& v1, std::vector<int> const& v2)
{
    std::unordered_map<int, int> elements;
    if (v1.size() != v2.size())
        return false;
    for (auto const a : v1) {
        ++elements[a];
    }
    for (auto const a : v2) {
        --elements[a];
    }
    for (auto const [_, balance] : elements) {
        if (balance != 0)
            return false;
    }
    return true;
}

TEST_CASE("dfp_tester", "[testers]")
{
    SECTION("All present")
    {
        std::vector<int> valid3_invalid4{1, 0, 2, 3, 3, 3, 3, 8, 7, 4};
        REQUIRE(IsDutchFlagPartitioned(valid3_invalid4, 3));
        REQUIRE(!IsDutchFlagPartitioned(valid3_invalid4, 4));

        std::vector<int> valid5_invalid1267{2, 2, 1, 5, 5, 6, 7, 6};
        REQUIRE(IsDutchFlagPartitioned(valid5_invalid1267, 5));
        REQUIRE(!IsDutchFlagPartitioned(valid5_invalid1267, 1));
        REQUIRE(!IsDutchFlagPartitioned(valid5_invalid1267, 2));
        REQUIRE(!IsDutchFlagPartitioned(valid5_invalid1267, 6));
        REQUIRE(!IsDutchFlagPartitioned(valid5_invalid1267, 7));
    }
    SECTION("Only one type present")
    {
        std::vector<int> threes{3, 3, 3, 3, 3, 3, 3, 3};
        REQUIRE(IsDutchFlagPartitioned(threes, 1));
        REQUIRE(IsDutchFlagPartitioned(threes, 3));
        REQUIRE(IsDutchFlagPartitioned(threes, 5));

        std::vector<int> one_three_one{1, 3, 1};
        REQUIRE(IsDutchFlagPartitioned(one_three_one, 0));
        REQUIRE(IsDutchFlagPartitioned(one_three_one, 4));
        REQUIRE(!IsDutchFlagPartitioned(one_three_one, 1));
        REQUIRE(!IsDutchFlagPartitioned(one_three_one, 2));
        REQUIRE(!IsDutchFlagPartitioned(one_three_one, 3));
    }
    SECTION("Only two types present")
    {
        std::vector<int> ones_threes{1, 1, 1, 3, 3, 3, 3, 3};
        REQUIRE(IsDutchFlagPartitioned(ones_threes, 0));
        REQUIRE(IsDutchFlagPartitioned(ones_threes, 1));
        REQUIRE(IsDutchFlagPartitioned(ones_threes, 2));
        REQUIRE(IsDutchFlagPartitioned(ones_threes, 3));
        REQUIRE(IsDutchFlagPartitioned(ones_threes, 4));

        std::vector<int> valid125678_invalid34{1, 4, 4, 4, 3, 6, 6, 8};
        REQUIRE(IsDutchFlagPartitioned(valid125678_invalid34, 1));
        REQUIRE(IsDutchFlagPartitioned(valid125678_invalid34, 2));
        REQUIRE(IsDutchFlagPartitioned(valid125678_invalid34, 5));
        REQUIRE(IsDutchFlagPartitioned(valid125678_invalid34, 6));
        REQUIRE(IsDutchFlagPartitioned(valid125678_invalid34, 7));
        REQUIRE(IsDutchFlagPartitioned(valid125678_invalid34, 8));
        REQUIRE(!IsDutchFlagPartitioned(valid125678_invalid34, 3));
        REQUIRE(!IsDutchFlagPartitioned(valid125678_invalid34, 4));
    }
}

TEST_CASE("same_elements_tester", "[testers]")
{
    std::vector<int> v1{1, 2, -2, 0, 3, 3, 100, 100, 4, 100, -2, 0};
    std::vector<int> same = v1;
    std::vector<int> with_one_extra_element = v1;
    with_one_extra_element.push_back(1);
    std::vector<int> with_one_element_changed = v1;
    with_one_element_changed[0] = 3;
    REQUIRE(SameElements(v1, same));
    REQUIRE(!SameElements(v1, with_one_extra_element));
    REQUIRE(!SameElements(v1, with_one_element_changed));
}

TEST_CASE("test1", "[5_1][DutchFlagPartition]")
{
    auto const input = GENERATE(std::vector<int>{1, 2, 2, -5, 3, 5, 4, 8},
                                std::vector<int>{1, 1, 1, 1, 1, 1, 1, 0},
                                std::vector<int>{7, 6, 5, 4, 3, 2, 1, 0},
                                std::vector<int>{2, 1, 3, 2, 1, 3, 2, 1});
    auto result = input;
    int const pivot_index = GENERATE(0, 1, 2, 3, 4, 5, 6, 7);
    int const pivot = input[pivot_index];
    DutchFlagPartition(result, pivot_index);
    CHECK(SameElements(input, result));
    CHECK(IsDutchFlagPartitioned(result, pivot));
}