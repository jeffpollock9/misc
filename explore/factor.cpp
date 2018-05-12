#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <fmt/format.h>

namespace detail
{

struct start_index
{
    explicit start_index(const int value) : value_(value)
    {}

    int operator()()
    {
        return value_++;
    }

private:
    int value_ = 0;
};

template <typename... Strings>
std::unordered_map<std::string, int> string_int_map(start_index incrementer,
                                                    Strings&&... strings)
{
    return {{strings, incrementer()}...};
}

} // namespace detail

#define STRINGIZE(s, data, elem) BOOST_PP_STRINGIZE(elem)

#define FACTOR(NAME, LEVELS)                                                   \
    struct NAME                                                                \
    {                                                                          \
        enum class levels : int { BOOST_PP_SEQ_ENUM(LEVELS) };                 \
                                                                               \
        constexpr NAME() : value_(static_cast<levels>(0))                      \
        {}                                                                     \
                                                                               \
        constexpr explicit NAME(const int x) : value_(static_cast<levels>(x))  \
        {                                                                      \
            assert(x >= 0);                                                    \
            assert(x < size());                                                \
        }                                                                      \
                                                                               \
        constexpr explicit NAME(const levels x) : value_(x)                    \
        {}                                                                     \
                                                                               \
        explicit NAME(const std::string& x)                                    \
        {                                                                      \
            static const auto map =                                            \
                string_int_map(detail::start_index(0),                         \
                               BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(       \
                                   STRINGIZE, 0, LEVELS)));                    \
                                                                               \
            value_ = static_cast<levels>(map.at(x));                           \
        }                                                                      \
                                                                               \
        static constexpr int size()                                            \
        {                                                                      \
            return BOOST_PP_SEQ_SIZE(LEVELS);                                  \
        }                                                                      \
                                                                               \
        constexpr levels value() const                                         \
        {                                                                      \
            return value_;                                                     \
        }                                                                      \
                                                                               \
        constexpr operator int() const                                         \
        {                                                                      \
            return static_cast<int>(value_);                                   \
        }                                                                      \
                                                                               \
        std::string to_string() const                                          \
        {                                                                      \
            static const std::array<std::string, size()> names{                \
                {BOOST_PP_SEQ_ENUM(                                            \
                    BOOST_PP_SEQ_TRANSFORM(STRINGIZE, 0, LEVELS))}};           \
                                                                               \
            return names[this->operator int()];                                \
        }                                                                      \
                                                                               \
        friend std::ostream& operator<<(std::ostream& os, const NAME& x)       \
        {                                                                      \
            os << x.to_string();                                               \
            return os;                                                         \
        }                                                                      \
                                                                               \
    private:                                                                   \
        levels value_;                                                         \
    };

FACTOR(cowboy, (good)(bad)(ugly))

int main()
{
    const cowboy clint("good");
    constexpr cowboy lee(1);
    constexpr cowboy eli(cowboy::levels::ugly);

    std::cout << "std::cout << clint: " << clint << "\n";

    fmt::print("clint.to_string(): {}\n", clint.to_string());
    fmt::print("clint.size(): {}\n", clint.size());
    fmt::print("clint == 0: {}\n", clint == 0);
    fmt::print("1 == lee: {}\n", 1 == lee);
    fmt::print("clint == eli: {}\n", clint == eli);
    fmt::print("clint.value() == cowboy::levels::good: {}\n",
               clint.value() == cowboy::levels::good);

    return 0;
}
