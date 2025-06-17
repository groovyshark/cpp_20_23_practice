#include <iostream>
#include <numeric>
#include <vector>
#include <ranges>
#include <concepts>

template <typename T>
concept DivisibleAndMultipliable = requires(T a, T b) {
    { a / b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
};

template <typename T>
concept HasSizeMethod = requires(T a) {
    { a.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept NumericContainer = std::ranges::range<T> &&
    std::convertible_to<std::ranges::range_value_t<T>, int>;


template <DivisibleAndMultipliable T>
T calculate(T a, T b) {
    return (a * b) / (a + b);
}

template <HasSizeMethod T>
std::size_t getSize(const T& x) {
    return x.size();
}

template <NumericContainer C>
int numericSum(const C& container) {
    return std::accumulate(container.begin(), container.end(), 0);
}