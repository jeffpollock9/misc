#include <algorithm>
#include <random>

#include <benchmark/benchmark.h>

#include "add_cpu_openmp.hpp"
#include "add_cpu_serial.hpp"
#include "add_cuda.hpp"
#include "add_thrust.hpp"

constexpr int N = 1 << 20;

struct fixture : benchmark::Fixture
{
    void SetUp(benchmark::State&) final
    {
        std::mt19937 rng;
        std::uniform_real_distribution<float> dist(0.0, 1.0);

        x = new float[N];
        y = new float[N];
        z = new float[N];

        std::generate_n(x, N, [&rng, &dist] { return dist(rng); });
        std::generate_n(y, N, [&rng, &dist] { return dist(rng); });
    }

    void TearDown(benchmark::State&) final
    {
        delete[] x;
        delete[] y;
        delete[] z;
    }

    float* x;
    float* y;
    float* z;
};

void add_state_counters(benchmark::State& state,
                        const float* x,
                        const float* y,
                        const float* z)
{
    const int M = N - 1;

    state.counters["x"]   = x[M];
    state.counters["y"]   = y[M];
    state.counters["z"]   = z[M];
    state.counters["ans"] = x[M] + y[M];
}

BENCHMARK_F(fixture, BM_add_cpu_serial)(benchmark::State& state)
{
    for (auto _ : state)
    {
        add_cpu_serial(N, x, y, z);
    }

    add_state_counters(state, x, y, z);
}

BENCHMARK_F(fixture, BM_add_cpu_openmp)(benchmark::State& state)
{
    for (auto _ : state)
    {
        add_cpu_openmp(N, x, y, z);
    }

    add_state_counters(state, x, y, z);
}

BENCHMARK_F(fixture, BM_add_cuda)(benchmark::State& state)
{
    for (auto _ : state)
    {
        add_cuda(N, x, y, z);
    }

    add_state_counters(state, x, y, z);
}

BENCHMARK_F(fixture, BM_add_thrust)(benchmark::State& state)
{
    for (auto _ : state)
    {
        add_thrust(N, x, y, z);
    }

    add_state_counters(state, x, y, z);
}

BENCHMARK_MAIN();
