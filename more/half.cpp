#include "math.hpp" // pi
#include "random.hpp"

#include <algorithm> // std::sort
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>

struct sample
{
    double x, px;
    auto operator<(const sample& s) { return x < s.x; }
};

int main()
{
    constexpr auto fn = [](double x) { return std::exp(-x / 2 / pi) * std::pow(std::sin(x), 2); };

    constexpr auto a = 0;
    constexpr auto b = 2 * pi;
    constexpr auto n = 10'000;

    rnd_gen rnd{a, b};

    sample samples[n];
    double sum = 0;

    for (auto i = 0; i < n; ++i)
    {
        auto x = rnd(), px = fn(x);
        samples[i] = {x, px};
        sum += px;
    }

    std::sort(std::begin(samples), std::end(samples));

    double acc = 0, half = 0;
    for (auto&& s : samples)
    {
        acc += s.px;
        if (acc >= sum / 2)
        {
            half = s.x;
            break;
        }
    }

    std::cout << std::fixed << std::setprecision(16);

    std::cout << "average = " << sum / n << std::endl;
    std::cout << "area = " << (b - a) * sum / n << std::endl;
    std::cout << "half = " << half << std::endl;

    return 0;
}
