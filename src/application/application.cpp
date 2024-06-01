/**
 * @file application.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-04
 */

#include "application.hpp"
#include "../image/image_builder.hpp"

#include <filesystem>

using namespace std;

Application::Application(const ObjectRegistry &objects_, const EncoderRegistry &encoders_)
    : objects(objects_), encoders(encoders_) {}

void Application::run(const ApplicationArgs &args)
{
    if (args.get_options().size() > 0 && args.get_options()[0].first == Opt::Help)
    {
        ApplicationArgs::print_help();
        return;
    }

    ImageBuilder image_builder(objects, args.get_image_config());

    filesystem::path render_to_path;
    for (const pair<Opt, string> &cmd : args.get_options())
    {
        switch (cmd.first)
        {
        case Opt::Help:
            ApplicationArgs::print_help();
            return;
        case Opt::Render:
            image_builder.render();
            render_to_path = cmd.second;
            string extension = render_to_path.extension().string();
            if (!extension.empty())
                extension = extension.substr(1);
            encoders.get(extension).encode_to_file(render_to_path, image_builder.get_image());
            break;
        }
    }
}
