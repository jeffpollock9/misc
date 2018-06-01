#include "add_cpu_serial.hpp"

void add_cpu_serial(const int n, const float* x, const float* y, float* z)
{
    for (int i = 0; i < n; ++i)
    {
        z[i] = x[i] + y[i];
    }
}
