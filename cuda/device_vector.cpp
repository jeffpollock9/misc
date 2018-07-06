#include <vector>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include "device_vector.hpp"

int main()
{
    { // copy from host to device then back
        std::vector<float> h1{42.0, 666.0};
        std::vector<float> h2(2);

        device_vector<float> d(h1.data(), h1.size());

        d.fill_host(h2.data());

        fmt::print("h1: {}, h2: {}\n", h1, h2);
    }

    { // copy random device vector to host
        int n  = 5;
        auto d = device_vector<float>::random(n);

        std::vector<float> h(n);

        d.fill_host(h.data());

        fmt::print("h: {}\n", h);
    }

    { // add 2 vectors
        int n = 5;

        std::vector<float> h1(n);
        std::vector<float> h2(n);
        std::vector<float> h3(n);

        auto d1 = device_vector<float>::random(n);
        auto d2 = device_vector<float>::random(n);
        device_vector<float> d3(n);

        add(d1, d2, d3);

        d1.fill_host(h1.data());
        d2.fill_host(h2.data());
        d3.fill_host(h3.data());

        fmt::print("h1: {}, h2: {}, h3: {}\n", h1, h2, h3);
    }

    return 0;
}
