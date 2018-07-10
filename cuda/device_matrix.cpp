#include <vector>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include "device_matrix.hpp"

int main()
{
    { // copy from host to device then back
        std::vector<float> h1{42.0, 666.0};
        std::vector<float> h2(2);

        device_matrix<float> d(h1.data(), h1.size(), 1);

        copy(d, h2.data());

        fmt::print("h1: {}, h2: {}\n", h1, h2);
    }

    { // copy random device vector to host
        int n  = 5;
        auto d = device_matrix<float>::random(n, 1);

        std::vector<float> h(n);

        copy(d, h.data());

        fmt::print("h: {}\n", h);
    }

    { // saxpy
        int n       = 5;
        float alpha = 0.5;

        std::vector<float> x_h(n);
        std::vector<float> y_h(n);

        curand_rng().seed(42);
        auto x = device_matrix<float>::random(n, 1);

        curand_rng().seed(42);
        auto y = device_matrix<float>::random(n, 1);

        copy(x, x_h.data());
        copy(y, y_h.data());

        fmt::print("x: {}, y: {}\n", x_h, y_h);

        axpy(alpha, x, y);

        copy(y, y_h.data());

        fmt::print("0.5 * x + y: {}\n", y_h);
    }

    return 0;
}
