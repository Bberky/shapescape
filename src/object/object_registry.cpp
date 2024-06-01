/**
 * @file object_registry.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-08
 */

#include "object_registry.hpp"
#include "../utils.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;
using namespace utils;

ObjectRegistry::ObjectRegistry(const object_map &objects_)
    : objects(objects_) {}

ObjectRegistry &ObjectRegistry::add(const string &name, obj_str_ctor constructor)
{
    objects.insert({name, constructor});

    return *this;
}

unique_ptr<Object> ObjectRegistry::parse_from_str(const string &src, bool print_err) const
{
    const auto &[obj_name, obj_params] = split_str_once(src);

    if (objects.count(obj_name) == 0)
    {
        if (print_err)
        {
            cerr << "supported objects are: " << endl;

            for (const auto &[obj_name, _] : objects)
                cerr << obj_name << endl;

            cerr << "...and compound object group" << endl;
        }

        throw invalid_argument("unsupported object: " + obj_name);
    }
    else if (obj_params.empty())
        throw invalid_argument(obj_name + ": no object parameters entered");

    return objects.at(obj_name)(obj_params);
}

bool ObjectRegistry::is_available(const string &name) const
{
    return objects.count(name) > 0;
}