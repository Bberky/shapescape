/**
 * @file utils.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "vec2.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace utils
{
    /**
     * @brief Try to open a file for reading in text mode
     *
     * @throws std::invalid_argument If file couldn't be opened
     * @param file Path to the file
     * @param mode Mode in which the file should be opened
     * @return std::ifstream
     */
    std::fstream try_open_file(const std::filesystem::path &file,
                               std::ios_base::openmode mode = std::ios_base::in);

    /**
     * @brief Split string once into two substrings based on
     * delimeter, e.g. split_str_once("Hello World !", ' ') will yield
     * ["Hello", "World !"]
     *
     * @param str String to split
     * @param delim Delimeter
     * @return std::pair<std::string, std::string>
     */
    std::pair<std::string, std::string> split_str_once(const std::string &str, char delim = ' ');

    /**
     * @brief Split string into substrings based on
     * delimeter, e.g. split_str("Hello World !", ' ') will yield
     * ["Hello", "World", "!"]. It ignores consecutive occurences of
     * delim, so split_str(" Hello    World   !  ", ' ') will still
     * yield ["Hello", "World", "!"]
     *
     * @param str String to split
     * @param delim Delimeter
     * @return std::vector<std::string>
     */
    std::vector<std::string> split_str(const std::string &str, char delim = ' ');

    /**
     * @brief Remove all occurence of consecutive whitespace from
     * given string by iterating over all characters and checking for consecutive
     * occurence of whitespace. This also removes any leading whitespace from the string
     *
     * @param src String to be parsed
     * @return std::string
     */
    std::string normalize_str(const std::string &src);

    /**
     * @brief Extract a named argument from string
     *
     * @throws std::invalid_argument If the names don't match
     * @param src String in the form "arg_name=arg_value"
     * @param name Name of the argument
     * @return std::string
     */
    std::string extract_arg(const std::string &src, const std::string &name);

    /**
     * @brief Extract a named integer argument from string
     *
     * @throws std::invalid_argument If the names don't match, if the entered value isn't a number,
     * or if the value isn't in the allowed range
     * @param src String in the form "arg_name=arg_value"
     * @param name Name of the argument
     * @param min Minimum allowed value
     * @param max Maximum allowed value
     * @return int
     */
    int extract_int_arg(const std::string &src, const std::string &name,
                        int min = 0, int max = std::numeric_limits<int>::max());

    /**
     * @brief Parse semicolon delimeted string of vertices into vector of
     * Coords.
     *
     * @throws std::invalid_argument If the string couldn't be parsed, or
     * if the string doesn't contain the desired number of vertices
     * @param src String in the form ((x0,y0);(x1,y1);(x2,y2);...)
     * @param min Minimum number of vertices to be parsed
     * @param max Maximum number of vertices to be parsed
     * @return std::vector<Coords>
     */
    std::vector<Coords> parse_vertices(const std::string &src, unsigned int min = 2,
                                       unsigned int max = std::numeric_limits<int>::max());

    /**
     * @brief Check for fails in fstream
     *
     * @throws std::runtime_exception If something went wrong with the stream
     * @param stream Stream to be checked
     * @param filename Optional filename for prettier error message
     */
    void check_fstream(const std::fstream &stream, const std::string &filename = "");
}
