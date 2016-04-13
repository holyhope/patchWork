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

    static Figure *decode(char **message);

    std::string encode() const;

    static bool decodable(char *message);

    void show(ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    //virtual Figure *rotate(float angle)const ;

    //virtual Figure *translate(Point p) const;

    Figure *scale(float factor) const;

    //virtual Figure *homothety(Point p, float factor) const;

    //virtual Figure *axialSymetry() const ;

    //virtual Figure *centralSymetry() const;

    //virtual Figure *colorize() const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle) const;

    static void initialize();

private:
    const static std::string PREFIX;
    Point _centre;
    double _rayon;
};

#endif //PATCHWORK_CIRCLE_H
