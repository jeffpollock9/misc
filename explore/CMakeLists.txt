
add_executable(async async.cpp)
target_link_libraries(async misc fmt::fmt Threads::Threads)

add_executable(avx avx.cpp)
target_link_libraries(avx misc fmt::fmt)

add_executable(factor factor.cpp)
target_link_libraries(factor misc fmt::fmt Boost::boost)
