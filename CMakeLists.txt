cmake_minimum_required(VERSION 3.4)

project(misc LANGUAGES CXX CUDA VERSION 0.0.1)

add_library(misc INTERFACE)
add_library(misc_cuda INTERFACE)

target_compile_options(misc INTERFACE
    -std=c++17 -march=native -ffast-math -fdiagnostics-color=always -Wall -Wextra -Wpedantic)

target_compile_options(misc_cuda INTERFACE
    -std=c++14 -use_fast_math -arch=sm_61)

find_package(CUDA)
find_package(OpenMP)
find_package(Threads)
find_package(Boost)
find_package(blaze PATHS "$ENV{HOME}/workspace/blaze/install" NO_DEFAULT_PATH)
find_package(Eigen3 PATHS "$ENV{HOME}/workspace/eigen/install" NO_DEFAULT_PATH)
find_package(benchmark PATHS "$ENV{HOME}/workspace/benchmark/install" NO_DEFAULT_PATH)
find_package(fmt PATHS "$ENV{HOME}/workspace/fmt/install" NO_DEFAULT_PATH)

add_subdirectory(benchmarks)
add_subdirectory(explore)
add_subdirectory(cuda)
