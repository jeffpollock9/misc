add_executable(example-app example-app.cpp)
target_link_libraries(example-app ${TORCH_LIBRARIES})
target_compile_features(example-app PUBLIC cxx_std_11)
