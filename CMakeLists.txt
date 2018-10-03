cmake_minimum_required(VERSION 3.9)

project(misc LANGUAGES CXX CUDA VERSION 0.0.1)

add_library(misc INTERFACE)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# it's bad to use these non portable flags, but suits me :)
target_compile_options(misc INTERFACE -march=native -ffast-math -Wall -Wextra -Wpedantic)
target_compile_features(misc INTERFACE cxx_std_17)

find_package(OpenMP)
find_package(Threads)
find_package(PythonLibs 3)
find_package(Boost COMPONENTS python3 numpy-py3)
find_package(blaze PATHS "$ENV{HOME}/workspace/blaze/install" NO_DEFAULT_PATH)
find_package(Eigen3 PATHS "$ENV{HOME}/workspace/eigen/install" NO_DEFAULT_PATH)
find_package(benchmark PATHS "$ENV{HOME}/workspace/benchmark/install" NO_DEFAULT_PATH)
find_package(fmt PATHS "$ENV{HOME}/workspace/fmt/install" NO_DEFAULT_PATH)
find_package(nlohmann_json PATHS "$ENV{HOME}/workspace/nlohmann_json/install" NO_DEFAULT_PATH)

list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/workspace/libtorch-shared-with-deps-latest/libtorch")
find_package(Torch)

add_subdirectory(benchmarks)
add_subdirectory(explore)
add_subdirectory(cuda)
add_subdirectory(python)
add_subdirectory(json)
add_subdirectory(pytorch)
