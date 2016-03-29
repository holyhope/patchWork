#include "point.h"

Point::Point(int a, int b) : x(a), y(b)
{
}

int Point::getX() const
{
    return x;
}

void Point::setX(int a)
{
    x = a;
}

int Point::getY() const
{
    return x;
}

void Point::setY(int b)
{
    y = b;
}

Point Point::operator+ (const Point & p) const
{
    return Point(x + p.x, y + p.y);
}

Point & Point::operator+= (const Point & p)
{
    x += p.x;
    y += p.y;
    return *this;
}

Point & Point::operator= (const Point & p)
{
    if (this == &p)
        return *this;

    x = p.x;
    y = p.y;

    return *this;
}

ostream & operator<< (ostream & os, const Point & p)
{
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}