#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "color.hpp"

#include <algorithm> // std::clamp
#include <cmath> // std::lerp
#include <functional> // std::reference_wrapper
#include <ostream>

class image
{
    std::reference_wrapper<std::ostream> os_;
    int width_, height_;

    constexpr auto to_8bit(double v) { return static_cast<int>(std::lerp(0., 255., std::clamp(v, 0., 1.)) + .5); }

public:
    image(std::ostream& os, int width, int height) :
        os_{os}, width_{width}, height_{height}
    {
        os_.get() << "P3\n" << width_ << ' ' << height_ << "\n255\n";
    }

    constexpr auto width() const { return width_; }
    constexpr auto height() const { return height_; }

    auto& operator<<(const color3& c)
    {
        os_.get() << to_8bit(c.r()) << ' ' << to_8bit(c.g()) << ' ' << to_8bit(c.b()) << '\n';
        return (*this);
    };
};

#endif
