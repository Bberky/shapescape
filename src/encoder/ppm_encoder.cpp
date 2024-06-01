/**
 * @file ppm_encoder.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#include "ppm_encoder.hpp"
#include "../utils.hpp"

#include <fstream>
#include <vector>

using namespace std;
using namespace utils;

void PPMEncoder::encode_to_file(const filesystem::path &file, const Image &image) const
{
    fstream out = try_open_file(file, ios_base::out);
    int width = image.get_width(), height = image.get_height();

    // Output PPM header
    out << "P3" << endl;
    out << width << ' ' << height << endl;
    out << 255 << endl;

    // Create the image pixel by pixel
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            const Pixel &pixel = image.get_buffer()(x, y);
            out << +pixel.r << ' ' << +pixel.g << ' ' << +pixel.b << endl;
        }

    check_fstream(out, file.filename());
}

shared_ptr<Encoder> PPMEncoder::clone() const
{
    return make_shared<PPMEncoder>(*this);
}
