/**
 * @file ppm_encoder.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "encoder.hpp"

/**
 * @brief Encoder for encoding images into the Netpbm color image format.
 * <a href="https://netpbm.sourceforge.net/doc/ppm.html">Format reference</a>
 */
class PPMEncoder : public Encoder
{
public:
    /**
     * @brief Encode image into Netpbm format by simply outputting
     * each pixel into the grid as text
     *
     * @throws std::invalid_argument If the file couldn't be created or opened for writing
     * @throws std::runtime_exception If something went wrong with the file while writing into it
     * @param file File into which the image should be saved
     * @param image Image to be saved
     */
    void encode_to_file(const std::filesystem::path &file, const Image &image) const override;

    std::shared_ptr<Encoder> clone() const override;
};
