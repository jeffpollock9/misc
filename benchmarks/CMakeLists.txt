
add_executable(eigen_blaze eigen_blaze.cpp)
target_link_libraries(eigen_blaze
    misc
    blaze::blaze
    Eigen3::Eigen
    benchmark::benchmark
    OpenMP::OpenMP_CXX)

add_executable(pow pow.cpp)
target_link_libraries(pow misc benchmark::benchmark)
