#ifndef DEVICE_MATRIX_HPP_
#define DEVICE_MATRIX_HPP_

#include <stdexcept>
#include <string>

#include <cublas_v2.h>
#include <cuda_runtime_api.h>
#include <curand.h>

/////////////////////
// check_error.hpp //
/////////////////////

#ifdef __GNUC__
#define UNLIKELY(x) __builtin_expect(x, 0)
#endif

inline void check_cuda_error(const cudaError_t code)
{
    if (UNLIKELY(code != cudaSuccess))
    {
        throw std::runtime_error("cuda error code: " + std::to_string(code));
    }
}

inline void check_cublas_error(const cublasStatus_t code)
{
    if (UNLIKELY(code != CUBLAS_STATUS_SUCCESS))
    {
        throw std::runtime_error("cublas error code: " + std::to_string(code));
    }
}

inline void check_curand_error(const curandStatus_t code)
{
    if (UNLIKELY(code != CURAND_STATUS_SUCCESS))
    {
        throw std::runtime_error("curand error code: " + std::to_string(code));
    }
}

#undef UNLIKELY

///////////////////////
// cublas_handle.hpp //
///////////////////////

struct cublas_handle_wrapper
{
    cublas_handle_wrapper()
    {
        const auto code = cublasCreate(&handle_);

        check_cublas_error(code);
    }

    ~cublas_handle_wrapper()
    {
        const auto code = cublasDestroy(handle_);

        check_cublas_error(code);
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

//////////////////////////
// curand_generator.hpp //
//////////////////////////

struct curand_generator_wrapper
{
    curand_generator_wrapper()
    {
        const auto code =
            curandCreateGenerator(&gen_, CURAND_RNG_PSEUDO_DEFAULT);

        check_curand_error(code);
    }

    ~curand_generator_wrapper()
    {
        const auto code = curandDestroyGenerator(gen_);

        check_curand_error(code);
    }

    curandGenerator_t& value()
    {
        return gen_;
    }

    void seed(const unsigned long long seed   = 0xdeadbeef,
              const unsigned long long offset = 0)
    {
        const auto seed_code = curandSetPseudoRandomGeneratorSeed(gen_, seed);

        check_curand_error(seed_code);

        const auto offset_code = curandSetGeneratorOffset(gen_, offset);

        check_curand_error(offset_code);
    }

private:
    curandGenerator_t gen_;
};

inline curand_generator_wrapper& curand_gen()
{
    static curand_generator_wrapper gen;
    return gen;
}

////////////////
// random.hpp //
////////////////

inline void fill_random_uniform(float* const data, const int size)
{
    const auto code = curandGenerateUniform(curand_gen().value(), data, size);

    check_curand_error(code);
}

inline void fill_random_uniform(double* const data, const int size)
{
    const auto code =
        curandGenerateUniformDouble(curand_gen().value(), data, size);

    check_curand_error(code);
}

///////////////////////
// device_matrix.hpp //
///////////////////////

template <typename T>
struct device_matrix
{
    device_matrix() = default;

    device_matrix(const int rows, const int cols) : rows_(rows), cols_(cols)
    {
        const auto code = cudaMalloc((void**)&data_, bytes());

        check_cuda_error(code);
    }

    device_matrix(const T* const host, const int rows, const int cols)
        : device_matrix(rows, cols)
    {
        const auto code =
            cudaMemcpy(data(), host, bytes(), cudaMemcpyHostToDevice);

        check_cuda_error(code);
    }

    ~device_matrix()
    {
        const auto code = cudaFree(data());

        check_cuda_error(code);
    }

    static device_matrix random(const int rows, const int cols)
    {
        device_matrix x(rows, cols);

        fill_random_uniform(x.data(), x.size());

        return x;
    }

    int rows() const
    {
        return rows_;
    }

    int cols() const
    {
        return cols_;
    }

    int size() const
    {
        return rows() * cols();
    }

    int bytes() const
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
    T* data_  = nullptr;
    int rows_ = 0;
    int cols_ = 0;
};

template <typename T>
inline void copy(const device_matrix<T>& device, T* const host)
{
    const auto code =
        cudaMemcpy(host, device.data(), device.bytes(), cudaMemcpyDeviceToHost);

    check_cuda_error(code);
}

inline void axpy(const double alpha,
                 const device_matrix<double>& x,
                 device_matrix<double>& y)
{
    const auto code = cublasDaxpy(
        cublas_handle().value(), x.size(), &alpha, x.data(), 1, y.data(), 1);

    check_cublas_error(code);
}

inline void
axpy(const float alpha, const device_matrix<float>& x, device_matrix<float>& y)
{
    const auto code = cublasSaxpy(
        cublas_handle().value(), x.size(), &alpha, x.data(), 1, y.data(), 1);

    check_cublas_error(code);
}

inline void gemm(const double alpha,
                 const device_matrix<double>& A,
                 const device_matrix<double>& B,
                 const double beta,
                 device_matrix<double>& C)
{
    const int m = A.rows();
    const int n = B.cols();
    const int k = A.cols();

    const int ld = 1;

    const auto code = cublasDgemm(cublas_handle().value(),
                                  CUBLAS_OP_N,
                                  CUBLAS_OP_N,
                                  m,
                                  n,
                                  k,
                                  &alpha,
                                  A.data(),
                                  ld,
                                  B.data(),
                                  ld,
                                  &beta,
                                  C.data(),
                                  ld);

    check_cublas_error(code);
}

inline void gemm(const float alpha,
                 const device_matrix<float>& A,
                 const device_matrix<float>& B,
                 const float beta,
                 device_matrix<float>& C)
{
    const int m = A.rows();
    const int n = B.cols();
    const int k = A.cols();

    const int ld = 1;

    const auto code = cublasSgemm(cublas_handle().value(),
                                  CUBLAS_OP_N,
                                  CUBLAS_OP_N,
                                  m,
                                  n,
                                  k,
                                  &alpha,
                                  A.data(),
                                  ld,
                                  B.data(),
                                  ld,
                                  &beta,
                                  C.data(),
                                  ld);

    check_cublas_error(code);
}

#endif /* DEVICE_MATRIX_HPP_ */
