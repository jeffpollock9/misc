#include "add_cpu_openmp.hpp"

void add_cpu_openmp(const int n, const float* x, const float* y, float* z)
{
    #pragma omp parallel for schedule(static) num_threads(12)
    for (int i = 0; i < n; ++i)
    {
        z[i] = x[i] + y[i];
    }
}
