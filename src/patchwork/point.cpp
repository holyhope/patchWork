#include "point.hpp"

#include <iostream>

int Point::getX() const {
    return _x;
}

void Point::setX(int a) {
    _x = a;
}

int Point::getY() const {
    return _y;
}

void Point::setY(int b) {
    _y = b;
}

Point Point::operator+(const Point &p) const {
    return Point(_x + p._x, _y + p._y);
}

Point &Point::operator+=(const Point &p) {
    _x += p._x;
    _y += p._y;
    return *this;
}

Point &Point::operator=(const Point &p) {
    if (this == &p)
        return *this;

    _x = p._x;
    _y = p._y;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "Point(" << p._x << ";" << p._y << ")";
    return os;
}