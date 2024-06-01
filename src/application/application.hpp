/**
 * @file application.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-04
 */

#pragma once

#include "application_args.hpp"
#include "../encoder/encoder_registry.hpp"
#include "../object/object_registry.hpp"

/**
 * @brief Class representing the whole ShapeScape application
 */
class Application
{
    ObjectRegistry objects;
    EncoderRegistry encoders;

public:
    /**
     * @brief Construct a new Application object with given ObjectRegistry and EncoderRegistry
     *
     * @param objects_ Supported objects that are parseable from string
     * @param encoders_ Supported encoders
     */
    Application(const ObjectRegistry &objects_ = {}, const EncoderRegistry &encoders_ = {});

    /** Run the application with given args */
    void run(const ApplicationArgs &args);
};
