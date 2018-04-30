
#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

constexpr int N = 1000;

struct fixture : benchmark::Fixture
{
    void SetUp(benchmark::State&) override
    {
        std::mt19937 rng;
        std::uniform_real_distribution<double> dist1(0.0, 1.0);
        std::uniform_int_distribution<int> dist2(0, 25);

        std::generate_n(y.begin(), N, [&] { return dist1(rng); });
        std::generate_n(pow.begin(), N, [&] { return dist2(rng); });
    }

    std::array<double, N> y;
    std::array<int, N> pow;
};

/// \brief see https://github.com/ampl/gsl/blob/master/sys/pow_int.c
double gsl_pow_uint(double x, unsigned int n)
{
    double value = 1.0;

    do
    {
        if (n & 1)
        {
            value *= x;
        }
        n >>= 1;
        x *= x;
    } while (n);

    return value;
}

/// \brief see https://github.com/ampl/gsl/blob/master/sys/pow_int.c
double gsl_pow_int(double x, const int n)
{
    unsigned int un;

    if (n < 0)
    {
        x  = 1.0 / x;
        un = -n;
    }
    else
    {
        un = n;
    }

    return gsl_pow_uint(x, un);
}

double silly_pow(const double x, const int pow)
{
    double out = 1.0;
    for (int i = 0; i < pow; ++i)
    {
        out = out * x;
    }
    return out;
}

BENCHMARK_F(fixture, BM_silly_pow)(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int i = 0; i < N; ++i)
        {
            const double x = silly_pow(y[i], pow[i]);
            benchmark::DoNotOptimize(x);
        }
    }
    state.counters["pow(3.14, 3)"] = silly_pow(3.14, 3);
}

BENCHMARK_F(fixture, BM_std_pow)(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int i = 0; i < N; ++i)
        {
            const double x = std::pow(y[i], pow[i]);
            benchmark::DoNotOptimize(x);
        }
    }
    state.counters["pow(3.14, 3)"] = std::pow(3.14, 3);
}

BENCHMARK_F(fixture, BM_gsl_pow_int)(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int i = 0; i < N; ++i)
        {
            const double x = gsl_pow_int(y[i], pow[i]);
            benchmark::DoNotOptimize(x);
        }
    }
    state.counters["pow(3.14, 3)"] = gsl_pow_int(3.14, 3);
}

BENCHMARK_F(fixture, BM_gsl_pow_uint)(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (int i = 0; i < N; ++i)
        {
            const double x = gsl_pow_uint(y[i], pow[i]);
            benchmark::DoNotOptimize(x);
        }
    }
    state.counters["pow(3.14, 3)"] = gsl_pow_uint(3.14, 3);
}

BENCHMARK_MAIN()
