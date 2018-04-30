
#include <array>

#include <fmt/format.h>
#include <immintrin.h>

using vector4d = __m256d;

constexpr int n = 4;

void print(const char* msg, vector4d x)
{
    fmt::print("{}", msg);

    for (int i = 0; i < n - 1; ++i)
    {
        fmt::print("{}, ", x[i]);
    }

    fmt::print("{}\n", x[n - 1]);
}

int main()
{
    const vector4d x = _mm256_set_pd(3.0, 1.0, 0.0, 2.0);

    print("x = ", x);

    {
        const vector4d xpx = _mm256_add_pd(x, x);

        print("x + x = ", xpx);
    }

    {
        const vector4d m3  = _mm256_set1_pd(3.0);
        const vector4d xm3 = _mm256_mul_pd(m3, x);

        print("x * 3 = ", xm3);
    }

    {
        const vector4d d2  = _mm256_set1_pd(2.0);
        const vector4d xd2 = _mm256_div_pd(x, d2);

        print("x / 2 = ", xd2);
    }

    {
        const vector4d sqrt = _mm256_sqrt_pd(x);

        print("sqrt(x) = ", sqrt);
    }

    {
        const vector4d y     = _mm256_set_pd(2.0, -1.0, 7.0, 1.0);
        const vector4d mask  = x > y;
        const vector4d xgty0 = _mm256_and_pd(mask, x);

        print("y = ", y);
        print("x > y = ", mask);
        print("x > y ? x : 0 = ", xgty0);
    }

    return 0;
}
