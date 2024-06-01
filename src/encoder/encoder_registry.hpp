/**
 * @file encoder_registry.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#pragma once

#include "encoder.hpp"

#include <map>

/**
 * @brief Registry for all supported encoders.
 * Encoders are stored as key-value pairs where key is
 * the file format and value is the associated encoder
 */
class EncoderRegistry
{
    using encoder_map = std::map<std::string, std::shared_ptr<Encoder>>;

    encoder_map encoders;

public:
    /**
     * @brief Construct a new Encoder Registry object
     *
     * @param encoders_ Supported encoders
     */
    EncoderRegistry(const encoder_map &encoders_ = {});

    /**
     * @brief Add an encoder to the registry given a format
     * and an encoder
     *
     * @param key Name of the format
     * @param encoder Encoder which handles said format
     * @return EncoderRegistry&
     */
    EncoderRegistry &add(const std::string &key, const Encoder &encoder);

    /**
     * @brief Get an encoder from the registry
     *
     * @throws std::invalid_argument If the encoder wasn't registred
     * with given key beforehand
     * @param key Name of the format
     * @param print_err Indicator whether verbose error message should
     * be printed to std::cerr
     * @return const Encoder&
     */
    const Encoder &get(const std::string &key, bool print_err = true) const;
};
