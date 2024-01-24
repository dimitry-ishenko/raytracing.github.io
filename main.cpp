#include "array.hpp"
#include "color.hpp"
#include "image.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    image img{std::cout, 256, 256};

    for (int j = 0; j < img.height(); ++j)
    {
        std::cerr << "\rRemaining: " << (img.height() - j) << ' ' << std::flush;
        for (int i = 0; i < img.width(); ++i)
        {
            color3 pix{double(i) / img.width(), double(j) / img.height(), 0};
            img << pix;
        }
    }
    std::cerr << "\rDone.            " << std::endl;

    return 0;
}
