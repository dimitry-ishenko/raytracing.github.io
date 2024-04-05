#include "random.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
    rnd_gen rnd_11{-1, 1};
    std::cout << std::fixed << std::setprecision(16);

    for (std::size_t inside = 0, total = 0; total < std::numeric_limits<std::size_t>::max(); ++total)
    {
        auto x = rnd_11(), y = rnd_11();
        if (x * x + y * y < 1) ++inside;

        if (!(total % 1000000)) std::cout << "\rπ = " << 4. * inside / total << std::flush;
    }
    std::cout << std::endl;

    return 0;
}
