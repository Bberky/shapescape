/**
 * @file test2.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-03
 */

#include "../src/image/pixel.hpp"
#include "../src/image/image.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    cout << "TESTING: image" << endl;

    Pixel p("#fff");
    p = Pixel("#abcdef");
    p = Pixel("#1a2b3c");
    p = Pixel("#ABCDEF");
    try
    {
        p = Pixel("#1");
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
        p = Pixel("#rgb");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    Image i(100, 100);
    try
    {
        i = Image(-100, 2);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    cout
        << "ALL TESTS SUCCESSFUL" << endl;

    return EXIT_SUCCESS;
}
