#include "random.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    constexpr auto fn = [](double x){ return x * x;                    };
//  constexpr auto fn = [](double x){ return std::pow(std::sin(x), 5); };
//  constexpr auto fn = [](double x){ return std::log(std::sin(x));    };

    constexpr auto a = 0;
    constexpr auto b = 2;
    constexpr auto n = 1'000'000;

    rnd_gen rnd{a, b};

    double sum = 0;
    for (auto i = 0; i < n; ++i) sum += fn(rnd());
    sum = (b - a) * sum / n;

    std::cout << std::fixed << std::setprecision(16);

    std::cout << "I(x^2) = "         << sum << std::endl;
//  std::cout << "I(sin(x)^5) = "    << sum << std::endl;
//  std::cout << "I(log(sin(x))) = " << sum << std::endl;

    return 0;
}

