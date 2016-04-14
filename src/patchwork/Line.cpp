//
// Created by Pichou Maxime on 29/03/2016.
//

#include <cmath>
#include <cstdio>
#include "Line.h"

const std::string Line::PREFIX = std::string("LINE");

Figure *Line::copy() const {
    return new Line(_A, _B);
}

void Line::show(ostream &stream) const {
    stream << "Line(A:" << this->_A << ", B:" << this->_B << ")";
}

double Line::getWidth() const {
    Point C(_B.getX(), _A.getY());

    double xC_minus_xA = C.getX() - _A.getX();
    double yC_minus_yA = C.getY() - _A.getY();

    return sqrt((xC_minus_xA * xC_minus_xA) + (yC_minus_yA * yC_minus_yA));
}

void Line::initialize() {
    Figure::registerFigure(Line::decodable, Line::decode);
}

Figure *Line::decode(char **message) {
    Point *p1, *p2;
    *message = *message + PREFIX.size();
    p1 = Point::decode(message);
    p2 = Point::decode(message);
    return new Line(*p1, *p2);
}

std::string Line::encode() const {
    return PREFIX + _A.encode() + _B.encode();
}

bool Line::decodable(char *message) {
    return 0 == PREFIX.compare(0, PREFIX.size(), string(message));
}

double Line::getHeight() const {
    Point C(_B.getX(), _A.getY());

    double xC_minus_xB = C.getX() - _B.getX();
    double yC_minus_yB = C.getY() - _B.getY();

    return sqrt((xC_minus_xB * xC_minus_xB) + (yC_minus_yB * yC_minus_yB));
}

Figure *Line::scale(float factor) const {
    long newBx = lround(_B.getX() + (_B.getX() - _A.getX()) / perimeter() * factor);
    long newBy = lround(_B.getY() + (_B.getY() - _A.getY()) / perimeter() * factor);
    return new Line(Point(_A.getX(), _A.getY()), Point(newBx, newBy));
}


double Line::area() const {
    return perimeter();
}


double Line::perimeter() const {
    double xB_minus_xA = _B.getX() - _A.getX();
    double yB_minus_yA = _B.getY() - _A.getY();

    return sqrt((xB_minus_xA * xB_minus_xA) + (yB_minus_yA * yB_minus_yA));
}

Figure *Line::rotate(float angle, double center_x, double center_y) const {
    double radianAngle = angle / 180.0 * M_PI;
    center_x = (_A.getX() + _B.getX()) / 2.;
    center_y = (_A.getY() + _B.getY()) / 2.;

    long Ax_new = lround(
            cos(radianAngle) * (_A.getX() - center_x) - sin(radianAngle) * (_A.getY() - center_y) + center_x);
    long Ay_new = lround(
            sin(radianAngle) * (_A.getX() - center_x) + cos(radianAngle) * (_A.getY() - center_y) + center_y);

    long Bx_new = lround(
            cos(radianAngle) * (_B.getX() - center_x) - sin(radianAngle) * (_B.getY() - center_y) + center_x);
    long By_new = lround(
            sin(radianAngle) * (_B.getX() - center_x) + cos(radianAngle) * (_B.getY() - center_y) + center_y);

    return new Line(Point(Ax_new, Ay_new), Point(Bx_new, By_new));
}
