
#include <iterator>
#include <numeric>

#include <fmt/format.h>

// https://www.reddit.com/r/cpp/comments/8xny4u/const_auto_versus_const_auto_for_pointer_types/

void print(const fmt::color color, const int* const x, const int n)
{
    for (int i = 0; i < n; ++i)
    {
        fmt::print_colored(color, "i: {}, value: {}\n", i, x[i]);
    }
}

int main()
{
    // nasty raw pointer stuff to see what happens
    int n  = 10;
    int* p = new int[n];

    std::iota(p, p + n, 42);

    print(fmt::color::red, p, n);

    {
        // _can_ edit the data
        const auto q = p;

        q[0] = 666;

        print(fmt::color::blue, q, n);

        // can't change the pointer
        // q = nullptr;
    }

    {
        // _can't_ edit the data
        const auto* q = p;

        // q[0] = 666;

        print(fmt::color::green, q, n);

        // can change the pointer
        q = nullptr;
    }

    delete[] p;

    return 0;
}
