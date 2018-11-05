
add_executable(async async.cpp)
target_link_libraries(async misc fmt::fmt Threads::Threads)

add_executable(avx avx.cpp)
target_link_libraries(avx misc fmt::fmt)

add_executable(factor factor.cpp)
target_link_libraries(factor misc fmt::fmt Boost::boost)

add_executable(fmt fmt.cpp)
target_link_libraries(fmt misc fmt::fmt)

add_executable(bad_pointer bad_pointer.cpp)
target_link_libraries(bad_pointer misc fmt::fmt)

add_executable(match match.cpp)
target_link_libraries(match misc fmt::fmt)

add_executable(sample sample.cpp)
target_link_libraries(sample misc fmt::fmt)

add_executable(spdlog spdlog.cpp)
target_link_libraries(spdlog misc spdlog::spdlog)
target_compile_definitions(spdlog PRIVATE SPDLOG_TRACE_ON SPDLOG_DEBUG_ON)
