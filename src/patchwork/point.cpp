#include <iosfwd>
#include "point.hpp"

const std::string Point::PREFIX = "P";

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

Point *Point::decode(std::istream &message) {
    int x, y;

    message.ignore(PREFIX.size());
    message >> x;
    message.ignore(strlen(":"));
    message >> y;

    return new Point(x, y);
}

std::string Point::encode() const {
    return PREFIX + std::to_string(_x) + ":" + std::to_string(_y);
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
    if (this == &p) {
        return *this;
    }

    _x = p._x;
    _y = p._y;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "Point(" << p._x << ";" << p._y << ")";
    return os;
}

bool Point::operator==(const Point &p) const {
    return _x == p._x && _y == p._y;
}

