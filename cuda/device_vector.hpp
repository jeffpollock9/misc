#ifndef DEVICE_VECTOR_HPP_
#define DEVICE_VECTOR_HPP_

#include <cstddef>
#include <stdexcept>
#include <type_traits>

#include <cuda_runtime_api.h>
#include <curand.h>

#include "add_cuda.hpp"

void random_uniform(curandGenerator_t rng, float* data, std::size_t size)
{
    curandGenerateUniform(rng, data, size);
}

void random_uniform(curandGenerator_t rng, double* data, std::size_t size)
{
    curandGenerateUniformDouble(rng, data, size);
}

template <typename T>
struct device_vector
{
    device_vector(std::size_t size) : size_(size)
    {
        cudaMalloc((void**)&data_, bytes());
    }

    device_vector(T* data, std::size_t size) : device_vector(size)
    {
        cudaMemcpy(data_, data, bytes(), cudaMemcpyHostToDevice);
    }

    ~device_vector()
    {
        cudaFree(data_);
    }

    static device_vector random(std::size_t size,
                                unsigned long long seed = 0xdeadbeef)
    {
        device_vector x(size);

        curandGenerator_t rng;

        curandCreateGenerator(&rng, CURAND_RNG_PSEUDO_DEFAULT);
        curandSetPseudoRandomGeneratorSeed(rng, seed);
        random_uniform(rng, x.data(), x.size());
        curandDestroyGenerator(rng);

        return x;
    }

    void fill_host(T* data) const
    {
        cudaMemcpy(data, data_, bytes(), cudaMemcpyDeviceToHost);
    }

    std::size_t size() const
    {
        return size_;
    }

    std::size_t bytes() const
    {
        return size_ * sizeof(T);
    }

    T* data() const
    {
        return data_;
    }

private:
    T* data_;
    std::size_t size_;
};

template <typename T>
void add(const device_vector<T>& x,
         const device_vector<T>& y,
         device_vector<T>& z)
{
    add_device_vector(x.size(), x.data(), y.data(), z.data());
}

#endif /* DEVICE_VECTOR_HPP_ */
