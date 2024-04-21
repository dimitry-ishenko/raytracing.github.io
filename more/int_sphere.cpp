#include "math.hpp"
#include "random.hpp"
#include "vec.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

auto f(const vec3& d)
{
    // f = cos^2(th)
    return d.z() * d.z();
};

auto pdf(const vec3&)
{
    return 1 / (4 * pi);
}

int main()
{
    constexpr auto n = 1'000'000;

    double sum = 0;
    for (auto i = 0; i < n; ++i)
    {
        auto d = rnd_vec3();
        sum += f(d) / pdf(d);
    }
    sum = sum / n;

    std::cout << std::fixed << std::setprecision(16);
    std::cout << "I = " << sum << std::endl;

    return 0;
}
