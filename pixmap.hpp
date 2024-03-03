#ifndef PIXMAP_HPP
#define PIXMAP_HPP

#include "color.hpp"
#include "image.hpp"
#include "point.hpp"
#include "texture.hpp"

#include <algorithm> // std::clamp
#include <filesystem>

namespace fs = std::filesystem;

struct pixmap : texture
{
    explicit pixmap(const fs::path& path) : image{image::read_from(path)} { }

    virtual color3 value(const point2& uv, const point3&) const override
    {
        int x = image.width * uv.x();
        int y = image.height * (1 - uv.y());
        return image.pixel[y * image.width + x];
    }

private:
    struct image image;
};

#endif
