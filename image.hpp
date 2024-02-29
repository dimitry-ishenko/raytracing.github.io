#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "color.hpp"

#include <algorithm> // std::clamp
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <iostream>
namespace fs = std::filesystem;

struct image
{
    int width, height;
    std::vector<color3> pixel;

    image(int width, int height) :
        width{width}, height{height}
    {
        pixel.resize(width * height);
    }

    void save_to(const fs::path& path)
    {
        std::ofstream os;
        os.exceptions(os.failbit);
        os.open(path);

        os << magic << eol;
        os << width << ' ' << height << eol;
        os << max << eol;
        for (auto&& c : pixel) os << to_int(c.r()) << ' ' << to_int(c.g()) << ' ' << to_int(c.b()) << eol;
    }

    static image read_from(const fs::path& path)
    {
        std::ifstream is;
        is.exceptions(is.failbit);
        is.open(path);

        auto ss = read_line(is);
        if (ss.str() != magic) throw std::invalid_argument{"Invalid magic"};

        int width = -1, height = -1;
        ss = read_line(is);
        ss >> width >> height >> std::ws;
        if (width < 0 || height < 0) throw std::invalid_argument{"Invalid size"};

        int max_ = -1;
        ss = read_line(is);
        ss >> max_ >> std::ws;
        if (max_ != max) throw std::invalid_argument{"Invalid depth"};

        image image{width, height};

        for (auto& c : image.pixel)
        {
            int r = -1, g = -1, b = -1;
            ss = read_line(is);
            ss >> r >> g >> b >> std::ws;
            if (r < 0 || r > max || g < 0 || g > max || b < 0 || b > max) throw std::invalid_argument{"Invalid pixel"};

            c = to_color(r, g, b);
        }

        return image;
    }

    static constexpr auto magic = "P3";
    static constexpr auto eol = '\n';
    static constexpr auto max = 255;

private:
    static std::istringstream read_line(std::ifstream& is)
    {
        std::string s;

        do std::getline(is, s);
        while (s.size() < 1 || s[0] == '#');

        return std::istringstream{std::move(s)};
    }

    constexpr static int to_int(double v) { return std::clamp(v, 0., 1.) * max + .5; }
    constexpr static color3 to_color(double r, double g, double b) { return color3{r, g, b} / max; }
};

#endif
