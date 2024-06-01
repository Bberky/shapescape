/**
 * @file vec2.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-11
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

/**
 * @brief General two-dimensional vector,
 * which can be used for storing and working
 * with any numeric type
 *
 * @tparam T Numeric data type, checked at compile-time
 * by static_assert
 */
template <typename T = int>
class Vec2
{
    static_assert(std::is_arithmetic<T>::value, "T has to be a numeric type");

public:
    /** First component */
    T x;
    /** Second component */
    T y;

    /**
     * @brief Construct a new Vec2 object with given values
     *
     * @param x_ First component of the vector
     * @param y_ Second component of the vector
     */
    Vec2(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_){};

    /**
     * @brief Construct a new Vec2 object from given source
     * string in the form "(x,y)"
     *
     * @throws std::invalid_argument If the given string couldn't
     * be parsed
     * @param src String in the form "(x,y)"
     */
    explicit Vec2(const std::string &src)
    {
        std::stringstream is(src);
        char left_bracket, comma, right_bracket;

        is >> left_bracket >> x >> comma >> y >> right_bracket;

        if (left_bracket != '(' || comma != ',' || right_bracket != ')' ||
            is.fail() || is.rdbuf()->in_avail())
            throw std::invalid_argument("error parsing vector: " + src);
    };

    /** Addition-assignment operator */
    Vec2 &operator+=(const Vec2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    };

    /** Addition operator */
    Vec2 operator+(const Vec2 &rhs) const
    {
        Vec2 res(*this);
        res += rhs;

        return res;
    };

    /** Subtraction-assignment operator */
    Vec2 &operator-=(const Vec2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    };

    /** Subtraction operator */
    Vec2 operator-(const Vec2 &rhs) const
    {
        Vec2 res(*this);
        res -= rhs;

        return res;
    };

    /** Multiplication-assignment operator */
    Vec2 &operator*=(const Vec2 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;

        return *this;
    };

    /** Multiplication operator */
    Vec2 operator*(const Vec2 &rhs) const
    {
        Vec2 res(*this);
        res *= rhs;

        return res;
    };

    /** Equality comparison operator */
    bool operator==(const Vec2 &rhs) const
    {
        return (x == rhs.x) && (y == rhs.y);
    }

    /** Non-equality comparison operator */
    bool operator!=(const Vec2 &rhs) const
    {
        return !(*this == rhs);
    }
};

/**
 * @brief Set of coordinates in the Cartesian
 * plane, represented by two integers
 */
using Coords = Vec2<>;

/**
 * @brief Scale factor represented by two
 * real numbers, first of which represents
 * X-axis scaling and second Y-axis scaling
 */
using ScaleFactor = Vec2<double>;
