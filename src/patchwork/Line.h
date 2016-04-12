//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_LINE_H
#define PATCHWORK_LINE_H


#include "figure.hpp"
#include "point.hpp"

class Line : public Figure {
public:

    Line(const Point &_origin, const Point &_extremity)
            : _A(_origin), _B(_extremity) { }

    Figure *copy() const override;

    void show(ostream &stream) const override;

    double getWidth() const override;

    double getHeight() const override;

    Figure *scale(float factor) const override;

    double area() const override;

    double perimeter() const override;

    Figure *rotate(float angle) const override;

protected:
    Point _A;
    Point _B;

    friend std::ostream &operator<<(std::ostream &os, const Line &l);
};


#endif //PATCHWORK_LINE_H
