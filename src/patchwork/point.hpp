//
// Created by Pierre Peronnet on 12/04/2016.
//

#ifndef PATCHWORK_POINT_HPP_H
#define PATCHWORK_POINT_HPP_H

#include <iostream>

class Point {
public:
    Point(int a, int b) : _x(a), _y(b) {
    }

    virtual int getX() const;

    virtual void setX(int a);

    virtual int getY() const;

    virtual void setY(int b);

    virtual Point operator+(const Point &p) const;

    virtual Point &operator+=(const Point &p);

    virtual Point &operator=(const Point &p);

protected:
    int _x, _y;

    friend std::ostream &operator<<(std::ostream &os, const Point &p);
};

std::ostream &operator<<(std::ostream &os, const Point &p);

#endif //PATCHWORK_POINT_HPP_H
