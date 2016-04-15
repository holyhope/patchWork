//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_CIRCLE_H
#define PATCHWORK_CIRCLE_H

#include "Figure.hpp"
#include "point.hpp"
#include <iostream>


class Circle : public Figure {
public:

    Circle(const Point &centre = Point(0, 0), double rayon = 0)
            : _centre(centre), _rayon(rayon) { }

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

    bool operator==(const Circle &c) const;

private:
    const static std::string PREFIX;
    Point _centre;
    double _rayon;
};

#endif //PATCHWORK_CIRCLE_H
