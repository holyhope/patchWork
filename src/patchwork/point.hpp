#ifndef PATCHWORK_POINT_HPP
#define PATCHWORK_POINT_HPP

/**
 * \file point.hh
 * \brief A simple representation of a 2D point
 */

#include <iostream>
#include <iosfwd>

class Point {
public:
    /**
     * Constructor for a point.
     * \param a an integer of the coordinate X.
     * \param b an integer of the coordinate Y.
     */
    Point(int a, int b) : _x(a), _y(b) {
    }

    /**
     * Get the coordinate X of the point.
     * \return The coordinate X.
     */
    int getX() const;

    /**
     * Set the coordinate X of the point.
     * \param a the new coordinate X.
     */
    void setX(int a);

    /**
     * Get the coordinate Y of the point.
     * \return The coordinate Y.
     */
    int getY() const;

    /**
     * Set the coordinate Y of the point.
     * \param a the new coordinate Y.
     */
    void setY(int b);

    static Point *decode(std::istream &message);

    std::string encode() const;

    Point operator+(const Point &p) const;

    Point &operator+=(const Point &p);

    Point &operator=(const Point &p);

    bool operator==(const Point &p) const;

private:
    int _x, _y;
    static const std::string PREFIX;

    friend std::ostream &operator<<(std::ostream &os, const Point &p);
};

#endif //PATCHWORK_POINT_HPP_H
