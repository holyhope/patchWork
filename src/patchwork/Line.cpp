//
// Created by Pichou Maxime on 29/03/2016.
//

#include <cmath>
#include "Line.h"

Figure *Line::copy() const {
    return new Line(this->_A, this->_B);
}

void Line::show(ostream &stream) const {
    stream << "Line((" << this->_A << ")(" << this->_B << ")";
}


double Line::getWidth() const {
    Point C(_B.getX(),_A.getY());

    double xC_minus_xA = C.getX() - _A.getX();
    double yC_minus_yA = C.getY() - _A.getY();

    return sqrt((xC_minus_xA * xC_minus_xA) + (yC_minus_yA * yC_minus_yA));
}


double Line::getHeight() const {
    Point C(_B.getX(),_A.getY());

    double xC_minus_xB = C.getX() - _B.getX();
    double yC_minus_yB = C.getY() - _B.getY();

    return sqrt((xC_minus_xB * xC_minus_xB) + (yC_minus_yB * yC_minus_yB));
}

/*
 * TODO
 */
Figure *Line::scale(float factor) const {
    long newBx = lround(_B.getX() + (_B.getX() - _A.getX()) / perimeter() * factor);
    long newBy = lround(_B.getY() + (_B.getY() - _A.getY()) / perimeter() * factor);
    return new Line(Point(_A.getX(), _A.getY()), Point(newBx,newBy));
}


double Line::area() const {
    return perimeter();
}

/*
 * TODO
 */
double Line::perimeter() const {
    double xB_minus_xA = _B.getX() - _A.getX();
    double yB_minus_yA = _B.getY() - _A.getY();

    return sqrt((xB_minus_xA * xB_minus_xA) + (yB_minus_yA * yB_minus_yA));
}

Figure *Line::rotate(float angle) const {

    float radianAngle = angle / 180.0 * M_PI;
    float center_x = (_A.getX() + _B.getX()) / 2.;
    float center_y = (_A.getY() + _B.getY()) / 2.;

    long Ax_new = lround(cos(radianAngle) * (_A.getX()-center_x) - sin(radianAngle) * (_A.getY()-center_y) + center_x);
    long Ay_new = lround(sin(radianAngle) * (_A.getX()-center_x) + cos(radianAngle) * (_A.getY()-center_y) + center_y);

    long Bx_new = lround(cos(radianAngle) * (_B.getX()-center_x) - sin(radianAngle) * (_B.getY()-center_y) + center_x);
    long By_new = lround(sin(radianAngle) * (_B.getX()-center_x) + cos(radianAngle) * (_B.getY()-center_y) + center_y);

    //long Ax_new = lround((  (_A.getX() - center_x) * cos(radianAngle) + (_A.getY() - center_y) * sin(radianAngle) ) + center_x);
    //long Ay_new = lround(( -(_A.getX() - center_x) * sin(radianAngle) + (_A.getY() - center_y) * cos(radianAngle) ) + center_y);

    //long Bx_new = lround((  (_B.getX() - center_x) * cos(radianAngle) + (_B.getY() - center_y) * sin(radianAngle) ) + center_x);
    //long By_new = lround(( -(_B.getX() - center_x) * sin(radianAngle) + (_B.getY() - center_y) * cos(radianAngle) ) + center_y);

    return new Line(Point(Ax_new,Ay_new), Point(Bx_new,By_new));
}















