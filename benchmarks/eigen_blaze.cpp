#include <random>

#include <Eigen/Dense>
#include <benchmark/benchmark.h>
#include <blaze/Math.h>

using eigen_matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using blaze_matrix = blaze::DynamicMatrix<double>;

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

static void BM_eigen_matmul_serial(benchmark::State& state)
{
    const int n = state.range(0);

    Eigen::setNbThreads(1);

    const auto a = random<eigen_matrix>(n);
    const auto b = random<eigen_matrix>(n);

    for (auto _ : state)
    {
        const eigen_matrix c = a * b;
        benchmark::DoNotOptimize(c);
    }
}

static void BM_eigen_matmul_8_threads(benchmark::State& state)
{
    const int n = state.range(0);

    Eigen::setNbThreads(8);

    const auto a = random<eigen_matrix>(n);
    const auto b = random<eigen_matrix>(n);

    for (auto _ : state)
    {
        const eigen_matrix c = a * b;
        benchmark::DoNotOptimize(c);
    }
}

static void BM_eigen_inverse(benchmark::State& state)
{
    const int n = state.range(0);

    const auto a = random<eigen_matrix>(n);

    for (auto _ : state)
    {
        const eigen_matrix b = a.inverse();
        benchmark::DoNotOptimize(b);
    }
}

static void BM_blaze_matmul_serial(benchmark::State& state)
{
    const int n = state.range(0);

    blaze::setNumThreads(1);

    const auto a = random<blaze_matrix>(n);
    const auto b = random<blaze_matrix>(n);

    for (auto _ : state)
    {
        const blaze_matrix c = a * b;
        benchmark::DoNotOptimize(c);
    }
}

static void BM_blaze_matmul_8_threads(benchmark::State& state)
{
    const int n = state.range(0);

    blaze::setNumThreads(8);

    const auto a = random<blaze_matrix>(n);
    const auto b = random<blaze_matrix>(n);

    for (auto _ : state)
    {
        const blaze_matrix c = a * b;
        benchmark::DoNotOptimize(c);
    }
}

static void BM_blaze_inverse(benchmark::State& state)
{
    const int n = state.range(0);

    const auto a = random<blaze_matrix>(n);

    for (auto _ : state)
    {
        const blaze_matrix b = blaze::inv(a);
        benchmark::DoNotOptimize(b);
    }
}

BENCHMARK(BM_eigen_matmul_serial)->RangeMultiplier(2)->Range(8, 512);
BENCHMARK(BM_eigen_matmul_8_threads)->RangeMultiplier(2)->Range(8, 512);
BENCHMARK(BM_eigen_inverse)->RangeMultiplier(2)->Range(8, 512);

BENCHMARK(BM_blaze_matmul_serial)->RangeMultiplier(2)->Range(8, 512);
BENCHMARK(BM_blaze_matmul_8_threads)->RangeMultiplier(2)->Range(8, 512);
BENCHMARK(BM_blaze_inverse)->RangeMultiplier(2)->Range(8, 512);

BENCHMARK_MAIN();
