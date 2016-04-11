//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_LINE_H
#define PATCHWORK_LINE_H


#include "figure.hpp"

class Line : public Figure {


public:

    Line(const Point &_origin, const Point &_extremity)
            : _origin(_origin), _extremity(_extremity) { }

    virtual Figure *copy() const override;

    virtual void show(ostream &stream) const override;

    virtual double getWidth() const override;

    virtual double getHeight() const override;

    virtual Figure *scale(float factor) const override;

    virtual double area() const override;

    virtual double perimeter() const override;

private:
    Point _origin;
    Point _extremity;
};


#endif //PATCHWORK_LINE_H
