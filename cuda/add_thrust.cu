#include "add_thrust.hpp"

#include <thrust/copy.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>

void add_thrust(const int n, const float* x, const float* y, float* z)
{
    thrust::device_vector<float> x_d(x, x + n);
    thrust::device_vector<float> yz_d(y, y + n);

    thrust::transform(x_d.begin(),
                      x_d.end(),
                      yz_d.begin(),
                      yz_d.begin(),
                      thrust::plus<float>());

    thrust::copy(yz_d.begin(), yz_d.end(), z);
}
