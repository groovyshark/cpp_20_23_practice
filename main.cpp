#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <ranges>
#include <concepts>
#include <format>

template <typename R>
concept NumericRange = 
    std::ranges::range<R> &&
    std::is_arithmetic_v<std::ranges::range_value_t<R>>;

template <NumericRange R>
auto stats(const R& range) {
    auto [minV, maxV] = std::ranges::minmax_element(range);
    double mean = std::accumulate(range.begin(), range.end(), 0.0) 
                            / std::ranges::distance(range);

    return std::tuple{mean, *minV, *maxV};
}

int main() {
    auto [mean, min, max] = stats(std::vector<double>{1.5, 2.0, 3.0, 4.5});
    std::cout << std::format("Mean {}, Min {}, Max {}", mean, min, max); 
    return 0;
}
