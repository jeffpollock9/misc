cmake_minimum_required(VERSION 3.4)

project(misc LANGUAGES CXX VERSION 0.0.1)

add_library(misc INTERFACE)

target_include_directories(misc INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

target_compile_options(misc INTERFACE -std=c++17 -Wall -Wextra -Wpedantic)

find_package(Eigen3 CONFIG REQUIRED
    PATHS "/home/jeff/workspace/eigen/install")
find_package(benchmark CONFIG REQUIRED
    PATHS "/home/jeff/workspace/benchmark/install")
find_package(fmt CONFIG REQUIRED
    PATHS "/home/jeff/workspace/fmt/install")

add_executable(eigen_ops benchmarks/eigen_ops.cpp)

target_link_libraries(eigen_ops
    misc Eigen3::Eigen benchmark::benchmark)
