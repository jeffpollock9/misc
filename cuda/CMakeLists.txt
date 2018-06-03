
add_library(add_cpu add_cpu_serial.cpp add_cpu_openmp.cpp)
target_link_libraries(add_cpu PRIVATE misc OpenMP::OpenMP_CXX)

add_library(add_gpu add_cuda.cu)
target_link_libraries(add_gpu PRIVATE misc_cuda)

add_library(add_thrust add_thrust.cu)
target_link_libraries(add_thrust PRIVATE misc_cuda)
target_link_libraries(add_thrust PRIVATE fmt::fmt) # TEMP

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark misc add_cpu add_gpu add_thrust benchmark::benchmark)
