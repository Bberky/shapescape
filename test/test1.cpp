/**
 * @file main.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-31
 */

#include "../src/utils.hpp"
#include "../src/vec2.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace utils;

int main()
{
    cout << "TESTING: utils" << endl;

    fstream stream = try_open_file("zadani.txt");
    try
    {
        try_open_file("zadanie.txt");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    check_fstream(stream);
    stream.setstate(ios_base::failbit);
    try
    {
        check_fstream(stream);
        assert(false);
    }
    catch (const runtime_error &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    string s1 = "Hello World";
    pair<string, string> s1_split = split_str_once(s1);
    assert(s1_split.first == "Hello");
    assert(s1_split.second == "World");
    s1 = "HelloWorld";
    s1_split = split_str_once(s1);
    assert(s1_split.first == "HelloWorld");
    assert(s1_split.second == "");
    s1 = "Hello=World";
    s1_split = split_str_once(s1, '=');
    assert(s1_split.first == "Hello");
    assert(s1_split.second == "World");
    s1 = "        Hello   World";
    s1_split = split_str_once(s1);
    assert(s1_split.first == "");
    assert(s1_split.second == "       Hello   World");

    string s2 = "Hello World !";
    vector<string> s2_split = split_str(s2);
    assert(s2_split[0] == "Hello");
    assert(s2_split[1] == "World");
    assert(s2_split[2] == "!");
    s2 = "====Hello====World=!=====";
    s2_split = split_str(s2, '=');
    assert(s2_split[0] == "Hello");
    assert(s2_split[1] == "World");
    assert(s2_split[2] == "!");
    s2 = "pppppppppppppppppp ";
    s2_split = split_str(s2, 'p');
    assert(s2_split[0] == " ");

    string s3 = "  Hello \n\t  World \n\n\n !",
           s3_normalized = normalize_str(s3);
    assert(s3_normalized == "Hello World !");
    s3 = "   \t\r \n \n \t\t     ";
    s3_normalized = normalize_str(s3);
    assert(s3_normalized == "");
    s3 = "Hello World";
    s3_normalized = normalize_str(s3);
    assert(s3_normalized == s3);

    string s4 = "color=#fff",
           s4_val = extract_arg(s4, "color");
    assert(s4_val == "#fff");
    try
    {
        s4_val = extract_arg(s4, "colors");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    s4 = "color";
    try
    {
        s4_val = extract_arg(s4, "color");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    string s5 = "width=1";
    int s5_val = extract_int_arg(s5, "width");
    assert(s5_val == 1);
    s5 = "width=1+1";
    try
    {
        s5_val = extract_int_arg(s5, "width");
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
        s5_val = extract_int_arg(s5, "widths");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    s5 = "width=1.9";
    try
    {
        s5_val = extract_int_arg(s5, "width");
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    s5 = "width=1";
    try
    {
        s5_val = extract_int_arg(s5, "width", 2);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    string s6 = "((500,250);(500,750))";
    vector<Coords> s6_vertices = parse_vertices(s6);
    assert(s6_vertices.size() == 2);
    assert(s6_vertices[0] == Coords(500, 250));
    assert(s6_vertices[1] != Coords(200, 0));
    assert(s6_vertices[1] == Coords(500, 750));
    s6 = "(0,0)";
    try
    {
        s6_vertices = parse_vertices(s6);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    s6 = "(500,250);(500,750))";
    try
    {
        s6_vertices = parse_vertices(s6);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    s6 = "((500,250);(a,750))";
    try
    {
        s6_vertices = parse_vertices(s6);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }
    s6 = "((500, 250); (0, 750))";
    try
    {
        s6_vertices = parse_vertices(s6, 3);
        assert(false);
    }
    catch (const invalid_argument &e)
    {
    }
    catch (...)
    {
        assert(false);
    }

    cout << "ALL TESTS SUCCESSFUL" << endl;

    return EXIT_SUCCESS;
}
