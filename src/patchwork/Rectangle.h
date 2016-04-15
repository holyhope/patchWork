#ifndef PATCHWORK_RETANGLE_H
#define PATCHWORK_RETANGLE_H

/**
 * \file Rectangle.h
 * \brief Representation of a rectangle, inherited from Figure class.
 */

#include "figure.hpp"
#include "point.hpp"
#include <iostream>

class Rectangle : public Figure {

public:
    /**
     * Constructor of Rectangle class
     * \param _origin the top-left corner point of the rectangle
     * \param extremity the bottom-right corner point of the rectangle
     */
    Rectangle(const Point &_origin, const Point &extremity)
            : _origin(_origin), _extremity(extremity) { }

    Figure *copy() const;

    static Figure *decode(std::istream &message);

    std::string encode() const;

    static bool decodable(std::istream &message);

    void show(std::ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    Figure *translate(Point p) const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle, double center_x, double center_y) const;

    static void initialize();

    bool operator==(const Rectangle &r) const;

private:
    static const std::string PREFIX;
    Point _origin;
    Point _extremity;
};

#endif //PATCHWORK_RETANGLE_H
