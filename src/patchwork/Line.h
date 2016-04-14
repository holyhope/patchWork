//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_LINE_H
#define PATCHWORK_LINE_H


#include "figure.hpp"
#include "point.hpp"
#include <iostream>

class Line : public Figure {
public:
    Line(const Point &_origin, const Point &_extremity)
            : _A(_origin), _B(_extremity) { }

    Figure *copy() const;

    static Figure *decode(char **message);

    std::string encode() const;

    static bool decodable(char *message);

    virtual void show(ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    Figure *scale(float factor) const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle, double center_x, double center_y) const;

    static void initialize();

private:
    static const std::string PREFIX;
    Point _A;
    Point _B;
};

#endif //PATCHWORK_LINE_H
