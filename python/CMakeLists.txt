
add_library(hello_boost_python SHARED hello_boost_python.cpp)
target_link_libraries(hello_boost_python misc Boost::python3 Boost::numpy-py3)
target_include_directories(hello_boost_python PRIVATE ${PYTHON_INCLUDE_DIRS})
set_target_properties(hello_boost_python PROPERTIES PREFIX "" OUTPUT_NAME hello_boost_python)

configure_file(hello_boost_python.py "${PROJECT_BINARY_DIR}/python/hello_boost_python.py")

add_custom_target(run_hello_boost_python
    COMMAND python3 hello_boost_python.py
    COMMENT "running python/hello_boost_python.py..."
    DEPENDS hello_boost_python)
