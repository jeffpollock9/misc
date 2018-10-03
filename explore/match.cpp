// https://www.meetup.com/CppLondon/events/238262489

#include <iostream>
#include <type_traits>
#include <utility>
#include <variant>

template <typename TF, typename... TFs>
struct overload_set : TF, overload_set<TFs...>
{
    using TF::operator();
    using overload_set<TFs...>::operator();

    template <typename TFFwd, typename... TRest>
    overload_set(TFFwd&& x, TRest&&... rest)
        : TF{std::forward<TFFwd>(x)},
          overload_set<TFs...>{std::forward<TRest>(rest)...}
    {}
};

template <typename TF>
struct overload_set<TF> : TF
{
    using TF::operator();

    template <typename TFFwd>
    overload_set(TFFwd&& f) : TF{std::forward<TFFwd>(f)}
    {}
};

template <typename... TFs>
auto overload(TFs&&... fs)
{
    return overload_set<std::remove_reference_t<TFs>...>{
        std::forward<TFs>(fs)...};
}

template <typename... TVariants>
constexpr auto match(TVariants&&... vs)
{
    return [&vs...](auto&&... fs) -> decltype(auto) {
        auto visitor = overload(std::forward<decltype(fs)>(fs)...);
        return std::visit(visitor, std::forward<TVariants>(vs)...);
    };
}

int main()
{
    using my_variant = std::variant<int, float, double>;

    my_variant v0{20.f};

    match(v0)([](int x) { std::cout << x << "i\n"; },
              [](float x) { std::cout << x << "f\n"; },
              [](double x) { std::cout << x << "d\n"; });
}
