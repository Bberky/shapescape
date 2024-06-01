/**
 * @file png_encoder.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#include "png_encoder.hpp"

#include <png.h>

using namespace std;

void PNGEncoder::encode_to_file(const filesystem::path &file, const Image &image) const
{
    int width = image.get_width(), height = image.get_height();

    // Open file and create neccessary png structs while
    // checking for failure and destroying objects if one occured
    FILE *out = fopen(file.c_str(), "wb");
    if (out == nullptr)
        throw invalid_argument("error opening file: " + file.string());

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr == nullptr)
    {
        fclose(out);
        throw runtime_error("error creating png write struct");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == nullptr)
    {
        fclose(out);
        png_destroy_write_struct(&png_ptr, nullptr);
        throw runtime_error("error creating png info struct");
    }

    // Initialize I/O and write headers
    png_init_io(png_ptr, out);
    png_set_IHDR(png_ptr, info_ptr, width, height, 8,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    // Write the png row by row, copying data from image buffer
    // into temporary vector *row*
    vector<unsigned char> row(sizeof(Pixel) * width);
    size_t row_index = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; x++)
        {
            const Pixel &pixel = image.get_buffer()(x, y);
            row[row_index++] = pixel.r;
            row[row_index++] = pixel.g;
            row[row_index++] = pixel.b;
        }

        png_bytep png_row = &row.front();
        png_write_row(png_ptr, png_row);

        // Check if any error occured
        if (setjmp(png_jmpbuf(png_ptr)))
        {
            png_write_end(png_ptr, info_ptr);
            png_destroy_write_struct(&png_ptr, &info_ptr);
            fclose(out);
            throw runtime_error("error writing png: " + file.filename().string());
        }

        row_index = 0;
    }

    // Final cleanup
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(out);
}

shared_ptr<Encoder> PNGEncoder::clone() const
{
    return make_shared<PNGEncoder>(*this);
}
