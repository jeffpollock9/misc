
add_library(misc_cuda INTERFACE)

target_compile_options(misc_cuda INTERFACE -use_fast_math -arch=sm_61)
target_compile_features(misc_cuda INTERFACE cxx_std_14)

# TODO: figure out a better way
add_library(cuda::cudart SHARED IMPORTED)
set_target_properties(cuda::cudart PROPERTIES
    IMPORTED_LOCATION "/usr/local/cuda-10.0/targets/x86_64-linux/lib/libcudart.so"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}")

add_library(cuda::curand SHARED IMPORTED)
set_target_properties(cuda::curand PROPERTIES
    IMPORTED_LOCATION "/usr/local/cuda-10.0/targets/x86_64-linux/lib/libcurand.so"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}")

add_library(cuda::cublas SHARED IMPORTED)
set_target_properties(cuda::cublas PROPERTIES
    IMPORTED_LOCATION "/usr/local/cuda-10.0/targets/x86_64-linux/lib/libcublas.so"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}")

add_library(add_cpu add_cpu_serial.cpp add_cpu_openmp.cpp)
target_link_libraries(add_cpu PRIVATE misc OpenMP::OpenMP_CXX)

add_library(add_gpu add_cuda.cu)
target_link_libraries(add_gpu PRIVATE misc_cuda)

add_library(add_thrust add_thrust.cu)
target_link_libraries(add_thrust PRIVATE misc_cuda)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark misc add_cpu add_gpu add_thrust benchmark::benchmark)

add_executable(device_matrix device_matrix.cpp)
target_link_libraries(device_matrix misc add_gpu fmt::fmt cuda::cudart cuda::curand cuda::cublas)
