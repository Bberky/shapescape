/**
 * @file bmp_encoder.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#include "bmp_encoder.hpp"
#include "../utils.hpp"

#include <array>
#include <fstream>

using namespace std;
using namespace utils;

void BMPEncoder::encode_to_file(const filesystem::path &file, const Image &image) const
{
    fstream out = try_open_file(file, ios_base::binary | ios_base::out);
    int width = image.get_width(), height = image.get_height();
    array<unsigned char, BMP_FILE_HEADER_SIZE> file_header;
    array<unsigned char, BMP_INFO_HEADER_SIZE> info_header;
    long file_size = image.get_size() + BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

    std::copy(BMP_FILE_HEADER, BMP_FILE_HEADER + BMP_FILE_HEADER_SIZE, file_header.begin());
    std::copy(BMP_INFO_HEADER, BMP_INFO_HEADER + BMP_INFO_HEADER_SIZE, info_header.begin());

    // Set image-specific info in the file header
    for (size_t i = 0; i < 4; i++)
        file_header[i + 2] = static_cast<unsigned char>(file_size >> (i * 8));
    // Set image-specific info in the info header
    for (size_t i = 0; i < 4; i++)
        info_header[i + 4] = static_cast<unsigned char>(width >> (i * 8));
    for (size_t i = 0; i < 4; i++)
        info_header[i + 8] = static_cast<unsigned char>(height >> (i * 8));

    // Write both headers into the output file
    for (const unsigned char &file_header_byte : file_header)
        out << file_header_byte;
    for (const unsigned char &info_header_byte : info_header)
        out << info_header_byte;

    int padding_size = (4 - (width * sizeof(Pixel)) % 4) % 4;

    // Write the image pixel by pixel
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            const Pixel &pixel = image.get_buffer()(x, y);
            out << pixel.b << pixel.g << pixel.r;
        }

        out.write(0, padding_size);
    }

    check_fstream(out, file.filename());
}

shared_ptr<Encoder> BMPEncoder::clone() const
{
    return make_shared<BMPEncoder>(*this);
}
