#include <fstream>
#include <map>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    json j;

    j["pi"]           = 3.14;
    j["vectors"]["1"] = {1.5, 2.5, 3.5, 4.5};
    j["vectors"]["2"] = {1, 2, 3, 4};

    std::ofstream ofile("nlohmann.json");
    ofile << j.dump();
    ofile.close();

    std::ifstream ifile("nlohmann.json");
    json p;
    ifile >> p;

    const double pi                 = p["pi"];
    const std::vector<double> first = p["vectors"]["1"];
    const std::vector<int> second   = p["vectors"]["2"];

    fmt::print("read [pi] as: {}\n", pi);
    fmt::print("read [vectors][1] as: {}\n", first);
    fmt::print("read [vectors][2] as: {}\n", second);

    return 0;
}
