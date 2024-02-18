#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "sphere.hpp"
#include "vec.hpp"

#include <random>

class rnd_gen
{
    inline static std::mt19937 gen;
    std::uniform_real_distribution<double> dist;

public:
    rnd_gen(double min, double max) : dist{min, max} { }
    auto operator()() { return dist(gen); }
};

inline auto rnd()
{
    static rnd_gen rnd{0, 1};
    return rnd();
}

inline auto rnd_disk3()
{
    static rnd_gen rnd{-1, 1};

    vec3 v{rnd(), rnd(), 0};
    for (; len_2(v) > 1; v = vec3{rnd(), rnd(), 0});
    return v;
}

inline auto rnd_sphere3()
{
    static rnd_gen rnd{-1, 1};

    vec3 v{rnd(), rnd(), rnd()};
    for (; len_2(v) > 1; v = vec3{rnd(), rnd(), rnd()});
    return v;
}

#endif
