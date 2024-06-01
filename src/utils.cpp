/**
 * @file utils.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#include "utils.hpp"
#include "vec2.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

fstream utils::try_open_file(const filesystem::path &file, ios_base::openmode mode)
{
    fstream stream(file, mode);

    if (!stream.is_open() || stream.fail())
        throw invalid_argument("failed to open file: " + file.string());

    return stream;
}

pair<string, string> utils::split_str_once(const string &str, char delim)
{
    pair<string, string> res;
    stringstream ss(str);

    getline(ss, res.first, delim);

    if (ss.peek() != -1)
        res.second = ss.str().substr(ss.tellg());

    return res;
}

vector<string> utils::split_str(const string &str, char delim)
{
    vector<string> res;
    stringstream ss(str);
    string piece;

    while (getline(ss, piece, delim))
        if (piece.length() != 0)
            res.push_back(piece);

    return res;
}

string utils::normalize_str(const string &src)
{
    string res;

    unique_copy(src.begin(), src.end(), back_insert_iterator<string>(res),
                [](char a, char b)
                { return isspace(a) && isspace(b); });

    if (!res.empty() && isspace(res[0]))
        res = res.substr(1);

    return res;
}

string utils::extract_arg(const string &src, const string &name)
{
    const auto &[arg_name, arg_val] = split_str_once(src, '=');

    if (arg_name != name)
        throw invalid_argument("unknown argument: " + arg_name + "\nexpected: " + name);
    else if (arg_val.empty())
        throw invalid_argument("no value given for argument: " + arg_name);

    return arg_val;
}

int utils::extract_int_arg(const string &src, const string &name, int min, int max)
{
    const invalid_argument err(name + " has to be an integer");
    string arg_val = extract_arg(src, name);
    bool has_sign = arg_val[0] == '-' || arg_val[0] == '+';

    if (!all_of(arg_val.begin() + (has_sign ? 1 : 0), arg_val.end(), [](char c)
                { return isdigit(c); }))
        throw err;

    int res;

    try
    {
        res = stoi(arg_val);
    }
    catch (...)
    {
        throw err;
    }

    if (res < min || res > max)
        throw invalid_argument(name + " has to be in range <" +
                               to_string(min) + ',' + to_string(max) + '>');

    return res;
}

vector<Coords> utils::parse_vertices(const string &src, unsigned int min, unsigned int max)
{
    if (src.front() != '(' || src.back() != ')')
        throw invalid_argument("error parsing vertices: " + src);

    vector<string> vertices_str = split_str(src.substr(1, src.find_last_of(')') - 1), ';');

    if (vertices_str.size() < min || vertices_str.size() > max)
        throw invalid_argument("wrong number of vertices entered: " + to_string(vertices_str.size()));

    vector<Coords> res;

    for (const string &vertex_str : vertices_str)
        res.push_back(Coords(vertex_str));

    return res;
}

void utils::check_fstream(const fstream &stream, const string &filename)
{
    if ((stream.fail() || stream.bad()) && (!stream.eof()))
        throw runtime_error("error working with file: " + filename);
}
