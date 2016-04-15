#ifndef PATCHWORK_POLYGON_H
#define PATCHWORK_POLYGON_H

/**
 * \file Polygon.h
 * \brief Representation of a figure with n points i.e Polygon
 */

#include <vector>
#include "figure.hpp"

class Polygon : public Figure {
public:
    Polygon()
            : _points() { }

    ~ Polygon();

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


    /**
     * Add a new point to the current polygon.
     * \param p the point to add
     */
    void addPoint(const Point &p);

    bool operator==(const Polygon &p) const;

private:
    static const std::string PREFIX;
    std::vector<Point *> _points;
};


#endif //PATCHWORK_POLYGON_H
