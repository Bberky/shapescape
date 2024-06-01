/**
 * @file test3.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-03
 */

#include "../src/object/object_registry.hpp"
#include "../src/object/line.hpp"
#include "../src/object/circle.hpp"
#include "../src/object/rectangle.hpp"
#include "../src/object/ellipse.hpp"
#include "../src/object/polygon.hpp"
#include "../src/object/curve.hpp"
#include "../src/object/spiral.hpp"
#include "../src/object/regular_polygon.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    cout << "TESTING: objects" << endl;

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

    supported_objects.parse_from_str("line ((100,100);(200,200)) width=4 color=#1A2B3C");
    supported_objects.parse_from_str("circle (250,250) radius=20");
    supported_objects.parse_from_str("rectangle ((100,100);(200,200)) color=#1A2B3C");
    supported_objects.parse_from_str("ellipse (100,100) radius_x=10 radius_y=20 color=#FFF");
    supported_objects.parse_from_str("spiral (50,50) rotations=5");
    supported_objects.parse_from_str("curve ((100,100);(150,150);(200,100))");
    supported_objects.parse_from_str("polygon ((100,100);(200,200);(100,300);(0,200))");
    supported_objects.parse_from_str("regular_polygon (100,100) n_sides=6 side=20");

    try
    {
        supported_objects.parse_from_str("");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("line");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("line");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("line (0,0)");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("ellipse (100,100) radius=9");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("polygon ((100,100);(90,90))");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("polygon ((0,0);(100,100);(200,200))");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("polygon ((0,0))");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("regular_polygon (0,0) n_sides=2");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("circle (0,0) radius=2 width=-1");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        supported_objects.parse_from_str("circle (0,0) radius=2 width=0");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    supported_objects.parse_from_str("circle (0,0) radius=2 width=2");

    cout << "ALL TESTS SUCCESSFUL" << endl;

    return EXIT_SUCCESS;
}
