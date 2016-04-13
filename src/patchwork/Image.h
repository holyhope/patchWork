//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_IMAGE_H
#define PATCHWORK_IMAGE_H


#include <list>
#include <set>
#include "figure.hpp"

class Image : public Figure {

public:
    enum {
        IMAGE_MAX = 50
    };

    Image(const Point &a = Point(0, 0))
            : _origin(a), _figures(), _count(0) { }

    void add(const Figure &f);

    virtual Figure *copy() const override;

    virtual ~Image() {
        std::set<Figure *>::iterator it(_figures.begin());
        std::set<Figure *>::iterator tmp;

        // iterate through the set and erase all figures
        for (; it != _figures.end();) {
            tmp = it;
            ++tmp;
            _figures.erase(it);
            _count--;
            it = tmp;

        }
    }

    virtual void show(ostream &stream) const override;

    virtual double getWidth() const override;

    virtual double getHeight() const override;

    virtual Figure *scale(float factor) const override;

    virtual double area() const override;

    virtual double perimeter() const override;

    virtual Figure *rotate(float angle) const override;

    friend bool operator<(const Figure &left, const Figure &right);

    int getCount();

    Figure *get(int i) const;


private:
    Point _origin;

    set<Figure *> _figures;

    int _count;
};


#endif //PATCHWORK_IMAGE_H
