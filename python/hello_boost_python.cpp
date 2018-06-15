
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

namespace bp = boost::python;
namespace np = boost::python::numpy;

auto greet()
{
    return "Hello world!";
}

auto keys(const bp::dict& d)
{
    return d.keys();
}

auto copy_dict(const bp::dict& d)
{
    const auto keys   = d.keys();
    const auto values = d.values();

    bp::dict y;

    for (int i = 0; i < len(keys); ++i)
    {
        const int key   = bp::extract<int>(keys[i]);
        const int value = bp::extract<int>(values[i]);

        y[key] = value;
    }

    return y;
}

auto list_plus(const bp::list& l, const int x)
{
    const int n = len(l);

    bp::list y;

    for (int i = 0; i < n; ++i)
    {
        y.append(l[i] + x);
    }

    return y;
}

auto none_list(const bp::list& l)
{
    const int n = len(l);

    bp::list y;

    const bp::object none;

    for (int i = 0; i < n; ++i)
    {
        y.append(none);
    }

    return y;
}

auto int_vector_plus(const std::vector<int>& v, const int x)
{
    std::vector<int> y(v.size());

    std::transform(
        v.cbegin(), v.cend(), y.begin(), [x](const int z) { return z + x; });

    return y;
}

auto array_plus(const np::ndarray& a, const double x)
{
    const int n           = a.get_shape()[0];
    const bp::tuple shape = bp::make_tuple(n);
    const np::dtype dtype = a.get_dtype();

    np::ndarray y = np::empty(shape, dtype);

    for (int i = 0; i < n; ++i)
    {
        y[i] = a[i] + x;
    }

    return y;
}

void oops()
{
    throw std::runtime_error("oops!");
}

struct foo
{
    foo() = default;

    foo(std::string msg) : msg_(std::move(msg))
    {}

    foo(std::string msg, const int rand) : msg_(std::move(msg)), rand_(rand)
    {}

    auto bar() const
    {
        return msg_;
    }

    auto rand() const
    {
        return rand_;
    }

    operator int() const
    {
        return rand_;
    }

    std::string readwrite_msg = "woo!";
    std::string readonly_msg  = "...woo?";

private:
    std::string msg_ = "NA";
    int rand_        = std::rand();
};

bool operator<(const foo& lhs, const foo& rhs)
{
    return lhs.rand() < rhs.rand();
}

foo operator+(const foo& lhs, const foo& rhs)
{
    return lhs.bar() + rhs.bar();
}

std::ostream& operator<<(std::ostream& os, const foo& f)
{
    return os << f.bar();
}

BOOST_PYTHON_MODULE(hello_boost_python)
{
    Py_Initialize();
    np::initialize();

    using namespace bp;

    def("greet", greet);
    def("keys", keys);
    def("copy_dict", copy_dict);
    def("list_plus", list_plus);
    def("none_list", none_list);
    def("int_vector_plus", int_vector_plus);
    def("array_plus", array_plus);
    def("oops", oops);

    class_<foo>("foo")
        .def(init<std::string>())
        .def(init<std::string, int>())
        .def_readwrite("readwrite_msg", &foo::readwrite_msg)
        .def_readonly("readonly_msg", &foo::readonly_msg)
        .def("rand", &foo::rand)
        .def("bar", &foo::bar)
        .def(self < self)
        .def(self + self)
        .def(self_ns::int_(self))
        .def(self_ns::str(self));

    class_<std::vector<int>>("IntVector")
        .def(vector_indexing_suite<std::vector<int>>());
}
