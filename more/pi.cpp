#include "random.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
    rnd_gen rnd_01{ 0, 1};
    rnd_gen rnd_11{-1, 1};

    std::cout << std::fixed << std::setprecision(16);

    std::size_t inside = 0, strat_inside = 0;
    constexpr std::size_t sqrt_total = 100000;

    for (std::size_t i = 0; i < sqrt_total; ++i)
    {
        for (std::size_t j = 0; j < sqrt_total; ++j)
        {
            auto x = rnd_11(), y = rnd_11();
            if (x * x + y * y < 1) ++inside;

            x = 2 * (i + rnd_01()) / sqrt_total - 1;
            y = 2 * (j + rnd_01()) / sqrt_total - 1;
            if (x * x + y * y < 1) ++strat_inside;
        }
        std::cout << "\ri = " << i << std::flush;
    }
    std::cout << std::endl;

    std::cout << "π = " << 4. * inside / (sqrt_total * sqrt_total) << std::endl;
    std::cout << "π = " << 4. * strat_inside / (sqrt_total * sqrt_total) << " strat" << std::endl;

    return 0;
}
