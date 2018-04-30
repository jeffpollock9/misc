
#include <chrono>
#include <future>
#include <thread>

#include <fmt/format.h>

int work(const int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    return n;
}

int main()
{
    auto n1 = std::async(std::launch::async, work, 2);
    auto n2 = std::async(std::launch::async, work, 3);

    fmt::print("{} --- {}\n", n1.get(), n2.get());

    auto n3 = std::async(std::launch::async, work, 5);

    while (n3.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
    {
        fmt::print("waiting...\n");
    }

    fmt::print("{}\ndone!\n", n3.get());

    return 0;
}
