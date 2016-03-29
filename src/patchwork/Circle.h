//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_CIRCLE_H
#define PATCHWORK_CIRCLE_H

#include <vector>
#include "Figure.hpp"
#include "point.h"


class Circle : public Figure{
public:

    Circle(const Point & centre = Point(0,0), double rayon = 0)
            : _centre(centre), _rayon(rayon){ }

    virtual Figure *copy() const;

    virtual void show(ostream &stream) const;

    virtual double getWidth() const;

    virtual double getHeight() const;

    //virtual Figure *rotate(float angle)const ;

    //virtual Figure *translate(Point p) const;

    virtual Figure *scale(float factor) const;

    //virtual Figure *homothety(Point p, float factor) const;

    //virtual Figure *axialSymetry() const ;

    //virtual Figure *centralSymetry() const;

    //virtual Figure *colorize() const;

    virtual double area() const;

    virtual double perimeter() const;

private:
    Point _centre;
    double _rayon;
};


#endif //PATCHWORK_CIRCLE_H
