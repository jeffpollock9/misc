
add_executable(nlohmann nlohmann.cpp)
target_link_libraries(nlohmann misc fmt::fmt nlohmann_json::nlohmann_json)
