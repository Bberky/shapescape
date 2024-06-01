/**
 * @file application_args.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-04
 */

#include "application_args.hpp"

#include <getopt.h>

using namespace std;

constexpr int opt_to_underlying(Opt opt) noexcept
{
    return static_cast<int>(opt);
}

const char *ApplicationArgs::help_msg =
    "Usage: <option(s)> SOURCE\n"
    "Options:\n"
    "\t-h, --help\tShow this help message\n"
    "\t-r, --render=FILENAME\tRender image into [FILENAME]\n";

ApplicationArgs::ApplicationArgs(int argc, char *argv[])
{
    parse_opts(argc, argv);

    if (argc <= 1)
        options.push_back({Opt::Help, ""});
    else if (optind != argc)
        image_config = argv[argc - 1];
}

void ApplicationArgs::parse_opts(int argc, char *argv[])
{
    const option opts[] = {
        {"help", no_argument, nullptr, opt_to_underlying(Opt::Help)},
        {"render", required_argument, nullptr, opt_to_underlying(Opt::Render)},
        {nullptr, no_argument, nullptr, 0}};

    while (true)
    {
        const int opt = getopt_long(argc, argv, "hr:", opts, 0);

        if (opt == -1)
            break;

        switch (opt)
        {
        case opt_to_underlying(Opt::Help):
            options.insert(options.begin(), {Opt::Help, ""});
            break;
        case opt_to_underlying(Opt::Render):
            options.push_back({Opt::Render, optarg});
        default:
            break;
        }
    }

    if (optind != (argc - 1) && optind < argc)
        throw invalid_argument("invalid argument entered: " + string(argv[optind]));
}

ostream &ApplicationArgs::print_help(ostream &os)
{
    os << help_msg;

    return os;
}

const vector<pair<Opt, string>> &ApplicationArgs::get_options() const
{
    return options;
}

const string &ApplicationArgs::get_image_config() const
{
    return image_config;
}
