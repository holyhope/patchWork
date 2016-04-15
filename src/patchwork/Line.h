#ifndef PATCHWORK_LINE_H
#define PATCHWORK_LINE_H

/**
 * \file Line.h
 * \brief Representation of a line, inherited from a Figure.
 */

#include "figure.hpp"
#include "point.hpp"
#include <iostream>

class Line : public Figure {
public:

    /**
     * Constructor of the Line Class
     * \param _origin The first point of the line.
     * \param _extremity The second point of the line.
     */
    Line(const Point &_origin, const Point &_extremity)
            : _A(_origin), _B(_extremity) { }

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

    bool operator==(const Line &l) const;

private:
    static const std::string PREFIX;
    Point _A;
    Point _B;
};

#endif //PATCHWORK_LINE_H
