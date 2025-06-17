#include <iostream>
#include <numeric>
#include <vector>
#include <list>
#include <ranges>
#include <concepts>

template <typename T>
concept Sortable = 
    std::ranges::range<T> &&
    std::random_access_iterator<std::ranges::iterator_t<T>> &&
    requires(std::ranges::range_value_t<T> a, std::ranges::range_value_t<T> b) {
        {a < b} -> std::convertible_to<bool>;
    };

template <typename F>
concept CallableWithInt = 
    std::invocable<F, int> &&
    requires(F f) {
        {f(42)} -> std::convertible_to<int>;
    };
    
template <typename T>
concept EqualityComparablePair = 
    requires {
        typename T::first_type;
        typename T::second_type;
    } &&
    std::equality_comparable<typename T::first_type> &&
    std::equality_comparable<typename T::second_type> &&
    std::equality_comparable<T>;
    
template<Sortable T>
void sortAndPrint(T& container) {
    std::sort(container.begin(), container.end());
    for (const auto& elem : container) {
        std::cout << elem << " ";
    }
    std::cout << '\n';
}

template<CallableWithInt F>
void applyAndPrint(F f) {
    for (int i = 0; i < 5; ++i)
        std::cout << f(i) << " ";
    std::cout << '\n';
}

template<EqualityComparablePair T>
bool are_equal(const T& a, const T& b) {
    return a == b;
}