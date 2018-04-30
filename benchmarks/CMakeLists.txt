
add_executable(eigen eigen.cpp)
target_link_libraries(eigen misc Eigen3::Eigen benchmark::benchmark)

add_executable(pow pow.cpp)
target_link_libraries(pow misc benchmark::benchmark)
