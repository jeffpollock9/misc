
#include <fmt/format.h>

int main()
{
    const float f = 0.123456789;

    fmt::print("print float f = 0.123456789 with {{:.2f}}= {:.2f}\n", f);
    fmt::print("print float f = 0.123456789 with {{:.4f}}= {:.4f}\n", f);

    return 0;
}
