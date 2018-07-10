#ifndef DEVICE_MATRIX_HPP_
#define DEVICE_MATRIX_HPP_

#include <cstddef>

#include <cublas_v2.h>
#include <cuda_runtime_api.h>
#include <curand.h>

struct cublas_handle_wrapper
{
    cublas_handle_wrapper()
    {
        cublasCreate(&handle_);
    }

    ~cublas_handle_wrapper()
    {
        cublasDestroy(handle_);
    }

    cublasHandle_t& value()
    {
        return handle_;
    }

private:
    cublasHandle_t handle_;
};

cublas_handle_wrapper& cublas_handle()
{
    static cublas_handle_wrapper handle;
    return handle;
}

struct curand_generator_wrapper
{
    curand_generator_wrapper()
    {
        curandCreateGenerator(&gen_, CURAND_RNG_PSEUDO_DEFAULT);
    }

    ~curand_generator_wrapper()
    {
        curandDestroyGenerator(gen_);
    }

    curandGenerator_t& value()
    {
        return gen_;
    }

    void seed(unsigned long long seed = 0xdeadbeef)
    {
        curandSetPseudoRandomGeneratorSeed(gen_, seed);
    }

private:
    curandGenerator_t gen_;
};

curand_generator_wrapper& curand_rng()
{
    static curand_generator_wrapper generator;
    return generator;
}

void fill_random_uniform(float* const data, const std::size_t size)
{
    curandGenerateUniform(curand_rng().value(), data, size);
}

void fill_random_uniform(double* const data, const std::size_t size)
{
    curandGenerateUniformDouble(curand_rng().value(), data, size);
}

template <typename T>
struct device_matrix
{
    device_matrix(const std::size_t rows, const std::size_t cols)
        : rows_(rows), cols_(cols)
    {
        cudaMalloc((void**)&data_, bytes());
    }

    device_matrix(const T* const host,
                  const std::size_t rows,
                  const std::size_t cols)
        : device_matrix(rows, cols)
    {
        cudaMemcpy(data(), host, bytes(), cudaMemcpyHostToDevice);
    }

    ~device_matrix()
    {
        cudaFree(data());
    }

    static device_matrix random(const std::size_t rows, const std::size_t cols)
    {
        device_matrix x(rows, cols);

        fill_random_uniform(x.data(), x.size());

        return x;
    }

    std::size_t rows() const
    {
        return rows_;
    }

    std::size_t cols() const
    {
        return cols_;
    }

    std::size_t size() const
    {
        return rows() * cols();
    }

    std::size_t bytes() const
    {
        return size() * sizeof(T);
    }

    T* data()
    {
        return data_;
    }

    const T* data() const
    {
        return data_;
    }

private:
    T* data_          = nullptr;
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
};

template <typename T>
void copy(const device_matrix<T>& device, T* const host)
{
    cudaMemcpy(host, device.data(), device.bytes(), cudaMemcpyDeviceToHost);
}

void axpy(const double alpha,
          const device_matrix<double> x,
          device_matrix<double>& y)
{
    cublasDaxpy_v2(
        cublas_handle().value(), x.size(), &alpha, x.data(), 1, y.data(), 1);
}

void axpy(const float alpha,
          const device_matrix<float> x,
          device_matrix<float>& y)
{
    cublasSaxpy_v2(
        cublas_handle().value(), x.size(), &alpha, x.data(), 1, y.data(), 1);
}

#endif /* DEVICE_MATRIX_HPP_ */
