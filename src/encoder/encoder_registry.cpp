/**
 * @file encoder_registry.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#include "encoder_registry.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;

EncoderRegistry::EncoderRegistry(const encoder_map &encoders_)
    : encoders(encoders_) {}

EncoderRegistry &EncoderRegistry::add(const string &key, const Encoder &encoder)
{
    encoders.insert({key, encoder.clone()});

    return *this;
}

const Encoder &EncoderRegistry::get(const string &key, bool print_err) const
{
    if (encoders.count(key) == 0)
    {
        if (print_err)
        {
            cerr << "supported formats are: " << endl;

            for (const auto &[fmt, _] : encoders)
                cerr << fmt << endl;
        }

        throw invalid_argument("unsupported format: " + key);
    }

    return *encoders.at(key);
}
