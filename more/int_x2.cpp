#include "random.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

auto f(double x)
{
    return x * x;
//  return std::pow(std::sin(x), 5);
//  return std::log(std::sin(x));
};

auto pdf(double x)
{
//  return .5;
//  return x / 2;
    return 3. / 8. * x * x;
}

auto cdf_inv(double d)
{
//  return 2 * d;
//  return std::sqrt(4 * d);
    return std::pow(8 * d, 1. / 3.);
}

int main()
{
//  constexpr auto n = 1'000'000;
    constexpr auto n = 1;

    double sum = 0;
    for (auto i = 0; i < n; ++i)
        if (auto d = rnd())
        {
            auto x = cdf_inv(d);
            sum += f(x) / pdf(x);
        }
    sum = sum / n;

    std::cout << std::fixed << std::setprecision(16);

    std::cout << "I(x^2) = "         << sum << std::endl;
//  std::cout << "I(sin(x)^5) = "    << sum << std::endl;
//  std::cout << "I(log(sin(x))) = " << sum << std::endl;

    return 0;
}

