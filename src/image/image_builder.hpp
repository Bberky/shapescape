/**
 * @file image_builder.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "image.hpp"
#include "../object/group.hpp"
#include "../object/object.hpp"
#include "../object/object_registry.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Interactive class for building images with objects,
 * which can be either added manually or by parsing a text file.
 */
class ImageBuilder
{
    /** Parameters for constructing an Image */
    using image_config = std::tuple<int, int, Pixel>;

    Image image;
    std::map<std::string, Group> groups;
    std::vector<std::unique_ptr<Object>> objects;
    /** Control variable to prevent re-rendering already rendered objects */
    bool is_rendered = false;

    /**
     * @brief Construct a new ImageBuilder object given the image constructor
     * parameters
     *
     * @param img_conf
     */
    ImageBuilder(const image_config &img_conf);

    /**
     * @brief Parse the first line of image configuration file
     *
     * @param filename File where the image config is located
     * @return image_config
     */
    static image_config parse_image_config(const std::string &filename);

    /**
     * @brief Parse Group object, reading multiple lines from image config
     *
     * @throws std::invalid_argument If the group couldn't be parsed,
     * or there was a problem with its name (object with the same name already exists or
     * it contains whitespace)
     * @param supported_objects Registry of objects that are parseable from string
     * @param is Input stream
     * @param group_name Name of the group
     */
    void parse_group(const ObjectRegistry &supported_objects, std::istream &is,
                     const std::string &group_name);

    /**
     * @brief Parse all the objects from image config
     *
     * @throws std::invalid_argument If the objects couldn't be parsed
     * @param supoprted_objects Registry of objects that are parseable from string
     * @param filename File where the image config is located
     */
    void parse_object_config(const ObjectRegistry &supoprted_objects, const std::string &filename);

public:
    /**
     * @brief Construct a new Image Builder object with given image configuration
     *
     * @param width Width of the image
     * @param height Height of the image
     * @param bg_color Optional background color of the image
     */
    ImageBuilder(int width, int height, const Pixel &bg_color = {});

    /**
     * @brief Construct a new Image Builder object
     *
     * @param supported_objects Registry of objects that are parseable from string
     * @param filename File where the image config is located
     */
    ImageBuilder(const ObjectRegistry &supported_objects, const std::string &filename);

    /** Image getter */
    const Image &get_image() const;

    /**
     * @brief
     *
     * @param obj
     * @return ImageBuilder&
     */
    ImageBuilder &add_object(const Object &obj);

    /**
     * @brief Render all the objects into the image
     */
    void render();
};
