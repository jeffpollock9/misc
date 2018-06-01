#include "add_cuda.hpp"

#include <cmath>

__global__ void
add_cuda_kernel(const int n, const float* x, const float* y, float* z)
{
    const int index  = blockIdx.x * blockDim.x + threadIdx.x;
    const int stride = blockDim.x * gridDim.x;

    for (int i = index; i < n; i += stride)
    {
        z[i] = x[i] + y[i];
    }
}

void add_cuda(const int n, const float* x, const float* y, float* z)
{
    const int size = n * sizeof(float);

    float* x_d;
    float* yz_d;

    cudaMalloc((void**)&x_d, size);
    cudaMalloc((void**)&yz_d, size);

    cudaMemcpy(x_d, x, size, cudaMemcpyHostToDevice);
    cudaMemcpy(yz_d, y, size, cudaMemcpyHostToDevice);

    const int block_size = 256;
    const int n_blocks   = std::ceil(n / static_cast<float>(block_size));

    add_cuda_kernel<<<n_blocks, block_size>>>(n, x_d, yz_d, yz_d);

    cudaDeviceSynchronize();

    cudaMemcpy(z, yz_d, size, cudaMemcpyDeviceToHost);

    cudaFree(x_d);
    cudaFree(yz_d);
}