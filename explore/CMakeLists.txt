
add_executable(async async.cpp)
target_link_libraries(async misc fmt::fmt Threads::Threads)

add_executable(avx avx.cpp)
target_link_libraries(avx misc fmt::fmt)
