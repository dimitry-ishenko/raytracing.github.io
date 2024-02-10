#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

inline auto& gen()
{
    static std::mt19937 gen_;
    return gen_;
}

class rnd_gen
{
    std::uniform_real_distribution<double> dist_;

public:
    rnd_gen(double min, double max) : dist_{min, max} { }
    auto operator()() { return dist_(gen()); }
};

#endif
