#include <iostream>
#include <numeric>
#include <vector>
#include <ranges>
#include <concepts>

template<typename R>
concept RangeOfInts = std::ranges::range<R> && 
                      std::convertible_to<std::ranges::range_value_t<R>, int>;

// Example of a function using the concept
template<RangeOfInts R>
constexpr int process(R&& data) {
    auto transformed = data
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * x; })
        | std::views::take(5);

    int sum = 0;
    for (const auto& value : transformed) {
        sum += value;
    }

    return sum;
}

int main() {
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    std::cout << "Runtime: " << process(v) << std::endl;

    constexpr std::array a{2, 4, 6, 8, 10, 11};
    std::cout << "Compile: " << process(a) << std::endl;
    static_assert(process(a) == 2*2 + 4*4 + 6*6 + 8*8 + 10*10);

    return 0;
}
