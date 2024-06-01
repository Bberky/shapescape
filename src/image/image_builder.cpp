/**
 * @file image_builder.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#include "image_builder.hpp"
#include "../utils.hpp"

#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace utils;

ImageBuilder::ImageBuilder(const image_config &img_conf)
    : ImageBuilder(get<0>(img_conf), get<1>(img_conf), get<2>(img_conf)) {}

ImageBuilder::image_config ImageBuilder::parse_image_config(const string &filename)
{
    const invalid_argument err("error parsing the image configuration");
    string line, cmd;
    fstream file_stream = try_open_file(filename);
    getline(file_stream, line);
    check_fstream(file_stream, filename);
    stringstream is(line);
    int width, height;
    Pixel bg;

    is >> cmd >> width >> height;

    if (cmd != "image")
        throw invalid_argument(
            "image definition needs to start with 'image'\ngiven command: " + cmd);
    else if (is.fail())
        throw err;

    if (is.rdbuf()->in_avail() > 0)
    {
        string background;
        is >> background;
        string bg_val = extract_arg(background, "background");
        bg = Pixel(bg_val);
    }

    string rest;
    is >> rest;

    if (!normalize_str(rest).empty())
        throw err;

    return make_tuple(width, height, bg);
}

void ImageBuilder::parse_group(const ObjectRegistry &supported_objects, istream &is,
                               const string &group_name)
{
    if (groups.count(group_name) > 0 || supported_objects.is_available(group_name))
        throw invalid_argument("object with name: " + group_name + " already exists");
    else if (group_name.empty() || any_of(group_name.begin(), group_name.end(), [](char c)
                                          { return isspace(c); }))
        throw invalid_argument("object name cannot contain whitespace: " + group_name);

    string line;
    Group group;
    bool ended_properly = false;

    while (getline(is, line))
    {
        line = normalize_str(line);

        if (line.empty())
            continue;

        const auto &[cmd, args] = split_str_once(line);

        if (cmd == "start_group")
            throw invalid_argument(
                "definition of a group inside of another group is not allowed");
        else if (cmd == "end_group")
        {
            ended_properly = true;
            break;
        }
        else if (groups.count(cmd) > 0)
        {
            Group inner_group(groups.at(cmd));
            inner_group.add_params(args);
            group.add_object(inner_group);
        }
        else
            group.add_object(*supported_objects.parse_from_str(line));
    }

    if (!ended_properly)
        throw invalid_argument("group " + group_name + " was never ended");

    groups.insert({group_name, group});
}

void ImageBuilder::parse_object_config(const ObjectRegistry &supported_objects,
                                       const string &filename)
{
    fstream is = try_open_file(filename);
    string line;
    getline(is, line); // Skip first line which is image config

    while (getline(is, line))
    {
        line = normalize_str(line);

        if (line.empty())
            continue;

        const auto &[cmd, args] = split_str_once(line);

        if (cmd == "start_group")
            parse_group(supported_objects, is, args);
        else if (cmd == "end_group")
            throw invalid_argument("end_group reached when no group was started");
        else if (groups.count(cmd) > 0)
        {
            Group group(groups.at(cmd));
            group.add_params(args);
            objects.push_back(make_unique<Group>(group));
        }
        else
            objects.push_back(supported_objects.parse_from_str(line));
    }

    check_fstream(is, filename);
}

ImageBuilder::ImageBuilder(int width, int height, const Pixel &bg_color)
    : image(width, height, bg_color) {}

ImageBuilder::ImageBuilder(const ObjectRegistry &supported_objects,
                           const string &filename)
    : ImageBuilder(parse_image_config(filename))
{
    parse_object_config(supported_objects, filename);
}

const Image &ImageBuilder::get_image() const
{
    return image;
}

ImageBuilder &ImageBuilder::add_object(const Object &obj)
{
    is_rendered = false;

    objects.push_back(obj.clone());

    return *this;
}

void ImageBuilder::render()
{
    if (is_rendered)
        return;

    for (const unique_ptr<Object> &obj : objects)
        obj->render(image, Coords(0, 0), ScaleFactor(1, 1));

    is_rendered = true;
}
