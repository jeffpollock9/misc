#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <ctime>
#include <random>

int main()
{
    constexpr int m = 6;
    constexpr int n = 3;

    std::mt19937 rng(std::time(nullptr));

    const auto x = [] {
        std::array<int, m> x;
        std::iota(x.begin(), x.end(), 1);
        return x;
    }();

    const auto y = [&] {
        std::array<int, n> y;
        std::sample(x.cbegin(), x.cend(), y.begin(), n, rng);
        return y;
    }();

    fmt::print("x: {}\n", x);
    fmt::print("y: {}\n", y);

    return 0;
}
