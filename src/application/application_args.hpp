/**
 * @file application_args.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-04
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Enum representing an option that can be
 * passed to the application
 */
enum class Opt : int
{
    Render = 'r',
    Help = 'h'
};

/**
 * @brief Cast the Opt enum as its underlying primitive type
 *
 * @param opt The option to be casted
 * @return constexpr int
 */
constexpr int opt_to_underlying(Opt opt) noexcept;

/**
 * @brief ApplicationArgs is for parsing the command line
 * options and arguments passed to the application upon
 * running it
 */
class ApplicationArgs
{

    static const char *help_msg;

    std::vector<std::pair<Opt, std::string>> options;
    std::string image_config;

    /** Parse the command line options and arguments */
    void parse_opts(int argc, char *argv[]);

public:
    /**
     * @brief Construct a new Application Args object and
     * parse command line options and arguments
     *
     * @param[in] argc Number of arguments entered
     * @param[in] argv Array of all the arguments
     */
    ApplicationArgs(int argc, char *argv[]);

    /** Print help message to os */
    static std::ostream &print_help(std::ostream &os = std::cerr);

    /** Options getter */
    const std::vector<std::pair<Opt, std::string>> &get_options() const;

    /** Image config getter */
    const std::string &get_image_config() const;
};