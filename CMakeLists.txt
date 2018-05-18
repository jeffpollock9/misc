cmake_minimum_required(VERSION 3.4)

project(misc LANGUAGES CXX VERSION 0.0.1)

add_library(misc INTERFACE)
target_compile_options(misc INTERFACE -std=c++17 -Wall -Wextra -Wpedantic)

find_package(OpenMP REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 CONFIG PATHS "$ENV{HOME}/workspace/eigen/install" NO_DEFAULT_PATH)
find_package(benchmark CONFIG PATHS "$ENV{HOME}/workspace/benchmark/install" NO_DEFAULT_PATH)
find_package(fmt CONFIG PATHS "$ENV{HOME}/workspace/fmt/install" NO_DEFAULT_PATH)

add_subdirectory(benchmarks)
add_subdirectory(explore)
