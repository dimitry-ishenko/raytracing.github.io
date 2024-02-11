#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "sphere.hpp"
#include "vec.hpp"

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

class rnd_vec3_gen
{
    std::uniform_real_distribution<double> dist_;

public:
    rnd_vec3_gen(double min, double max) : dist_{min, max} { }
    auto operator()() { return vec3{dist_(gen()), dist_(gen()), dist_(gen())}; }
};

class rnd_sphere3_gen
{
    rnd_vec3_gen gen_;

public:
    explicit rnd_sphere3_gen(double r) : gen_{-r, r} { }

    auto operator()()
    {
        vec3 v;
        do v = gen_(); while (len_2(v) > 1);
        return unit{v};
    }
};

#endif
