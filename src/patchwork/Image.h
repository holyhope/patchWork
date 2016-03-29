//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_IMAGE_H
#define PATCHWORK_IMAGE_H


#include <list>
#include "figure.hpp"

class Image : public Figure{

public:
    enum {IMAGE_MAX = 50};

    Image (const Point & a = Point(0,0))
            : _origin(a), _figures(), _count(0) { }

    void add(const Figure &f);

    virtual Figure *copy() const override ;

    virtual ~Image()
    {
        list<Figure *>::iterator it(_figures.begin());
        list<Figure *>::const_iterator end(_figures.end());

        while(it != end)
        {
            it = _figures.erase(it); /** erase is safe during list iteration */
            ++it;
        }
    }

    virtual void show(ostream &stream) const override ;

    virtual double getWidth() const override ;

    virtual double getHeight() const override ;

    virtual Figure *scale(float factor) const override ;

    virtual double area() const override ;

    virtual double perimeter() const override ;
private:
    Point _origin;

    list<Figure *> _figures;

    int _count;
};


#endif //PATCHWORK_IMAGE_H
