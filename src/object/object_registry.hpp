/**
 * @file object_registry.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-08
 */

#pragma once

#include "object.hpp"

#include <functional>
#include <map>
#include <string>

/**
 * @brief Registry for all supported objects,
 * which can be parsed form a single line of string input.
 * Objects are stored as key-value pairs where key is the
 * name of the object and value is associated static method
 * which constructs said object from source string
 */
class ObjectRegistry
{
    using obj_str_ctor = std::function<std::unique_ptr<Object>(const std::string &)>;
    using object_map = std::map<std::string, obj_str_ctor>;

    object_map objects;

public:
    /**
     * @brief Construct a new Object Registry object
     *
     * @param objects_ Supported objects
     */
    ObjectRegistry(const object_map &objects_ = {});

    /**
     * @brief Add an object to the registry
     *
     * @param name Name of the object
     * @param constructor Function or method which construct the object when
     * given a source string
     * @return ObjectRegistry&
     */
    ObjectRegistry &add(const std::string &name, obj_str_ctor constructor);

    /**
     * @brief Construct one of the objects from the registry given a
     * source string, the first whitespace delimeted word should be name
     * of an object which has been registered to the registry beforehand
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String to be parsed into an object
     * @param print_err Indicator whether verbose error message should
     * be printed to std::cerr
     * @return std::unique_ptr<Object>
     */
    std::unique_ptr<Object> parse_from_str(const std::string &src,
                                           bool print_err = true) const;

    /**
     * @brief Check whether given object is available from ObjectRegistry
     *
     * @param name Name of the object
     * @return true If the ObjectRegistry contains the given object,
     * otherwise false
     */
    bool is_available(const std::string &name) const;
};
