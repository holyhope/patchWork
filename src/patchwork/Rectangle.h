//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_RETANGLE_H
#define PATCHWORK_RETANGLE_H


#include "figure.hpp"
#include "point.hpp"
#include <iostream>

class Rectangle : public Figure {

public:
    Rectangle(const Point &_origin, const Point &extremity)
            : _origin(_origin), _extremity(extremity) { }

    Figure *copy() const;

    static Figure *decode(char **message);

    std::string encode() const;

    static bool decodable(char *message);

    void show(ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    Figure *scale(float factor) const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle, double center_x, double center_y) const;

    static void initialize();

private:
    static const std::string PREFIX;
    Point _origin;
    Point _extremity;
};

#endif //PATCHWORK_RETANGLE_H
