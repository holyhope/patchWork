//
// Created by Pierre Peronnet on 12/04/2016.
//

#ifndef PATCHWORK_POINT_HPP
#define PATCHWORK_POINT_HPP

#include <iostream>

class Point {
public:
    Point(int a, int b) : _x(a), _y(b) {
    }

    int getX() const;

    void setX(int a);

    int getY() const;

    void setY(int b);

    static Point *decode(std::istream &message);

    std::string encode() const;

    Point operator+(const Point &p) const;

    Point &operator+=(const Point &p);

    Point &operator=(const Point &p);

private:
    int _x, _y;

    friend std::ostream &operator<<(std::ostream &os, const Point &p);
};

#endif //PATCHWORK_POINT_HPP_H
