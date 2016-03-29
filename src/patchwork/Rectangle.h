//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_RETANGLE_H
#define PATCHWORK_RETANGLE_H


#include "figure.hpp"

class Rectangle : public Figure{

public:


    Rectangle(const Point &extremity, const Point &_origin)
            : _extremity(extremity), _origin(_origin) { }

    virtual Figure *copy() const override ;

    virtual void show(ostream &stream) const override ;

    virtual double getWidth() const override ;

    virtual double getHeight() const override ;

    virtual Figure *scale(float factor) const override ;

    virtual double area() const override ;

    virtual double perimeter() const override;
private:
    Point _origin;
    Point _extremity;
};


#endif //PATCHWORK_RETANGLE_H
