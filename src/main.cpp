/**
 * @file main.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-04
 */

#include "application/application.hpp"
#include "encoder/encoder_registry.hpp"
#include "encoder/ppm_encoder.hpp"
#include "encoder/bmp_encoder.hpp"
#include "encoder/png_encoder.hpp"
#include "object/object_registry.hpp"
#include "object/line.hpp"
#include "object/circle.hpp"
#include "object/rectangle.hpp"
#include "object/ellipse.hpp"
#include "object/polygon.hpp"
#include "object/curve.hpp"
#include "object/spiral.hpp"
#include "object/regular_polygon.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[])
{
    EncoderRegistry supported_encoders;
    supported_encoders
        .add("ppm", PPMEncoder())
        .add("bmp", BMPEncoder())
        .add("png", PNGEncoder());

    ObjectRegistry supported_objects;
    supported_objects
        .add("line", Line::parse_from_str)
        .add("circle", Circle::parse_from_str)
        .add("rectangle", Rectangle::parse_from_str)
        .add("ellipse", Ellipse::parse_from_str)
        .add("polygon", Polygon::parse_from_str)
        .add("curve", Curve::parse_from_str)
        .add("spiral", Spiral::parse_from_str)
        .add("regular_polygon", RegularPolygon::parse_from_str);

    try
    {
        Application(supported_objects, supported_encoders).run(ApplicationArgs(argc, argv));
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
