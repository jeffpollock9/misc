#include <random>

#include <Eigen/Dense>
#include <benchmark/benchmark.h>

using matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;

template <typename T>
T random(const int n)
{
    T x(n, n);

    std::uniform_real_distribution<double> runif(0.0, 1.0);
    std::mt19937 rng(42);

    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            x(i, j) = runif(rng);
        }
    }

    return x;
}

static void BM_matmul(benchmark::State& state)
{
    const int n = state.range(0);

    const auto a = random<matrix>(n);
    const auto b = random<matrix>(n);

    for (auto _ : state)
    {
        const matrix c = a * b;
        benchmark::DoNotOptimize(c);
    }
}

static void BM_inverse(benchmark::State& state)
{
    const int n = state.range(0);

    const auto a = random<matrix>(n);

    for (auto _ : state)
    {
        const matrix b = a.inverse();
        benchmark::DoNotOptimize(b);
    }
}

BENCHMARK(BM_matmul)->RangeMultiplier(2)->Range(8, 512);
BENCHMARK(BM_inverse)->RangeMultiplier(2)->Range(8, 512);

BENCHMARK_MAIN();
