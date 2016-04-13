//
// Created by Pichou Maxime on 29/03/2016.
//

#ifndef PATCHWORK_IMAGE_H
#define PATCHWORK_IMAGE_H


#include <list>
#include <set>
#include <iostream>
#include "figure.hpp"
#include "point.hpp"

class Image : public Figure {

public:
    enum {
        IMAGE_MAX = 50
    };

    Image(const Point &a = Point(0, 0))
            : _origin(a), _figures(), _count(0) { }

    void add(const Figure &f);

    Figure *copy() const;

    ~Image() {
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

    static Figure *decode(char **message);

    std::string encode() const;

    static bool decodable(char *message);

    void show(ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    Figure *scale(float factor) const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle) const;

    friend bool operator<(const Figure &left, const Figure &right);

    static void initialize();

private:
    static const std::string PREFIX;
    Point _origin;

    set<Figure *> _figures;

    int _count;
};

#endif //PATCHWORK_IMAGE_H
