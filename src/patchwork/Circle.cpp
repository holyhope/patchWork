//
// Created by Pichou Maxime on 29/03/2016.
//

#include <math.h>
#include "Circle.h"
#include "common.h"

const std::string Circle::PREFIX = std::string("CIRC");

/**
 * Fonction virtuelle de copie
 */
Figure *Circle::copy() const {
    return new Circle(this->_centre, this->_rayon);
}

void Circle::show(std::ostream &stream) const {
    stream << "Circle(Center:" << _centre << ", Radius:" << _rayon << ")";
}

Figure *Circle::decode(std::istream &message) {
    long radius, radiusCommaTmp, radiusComma, nbComma = 10;
    Point *center;

    message.ignore(PREFIX.size());
    message >> radius;
    message.get();
    message >> radiusComma;
    center = Point::decode(message);

    std::cout << radius << std::endl;
    std::cout << radiusComma << std::endl;

    radiusCommaTmp = radiusComma;
    while (0 < (radiusCommaTmp /= 10)) {
        nbComma *= 10;
    }

    return new Circle(*center, radius + (double) radiusComma / nbComma);
}

bool Circle::decodable(std::istream &message) {
    return startWith(message, PREFIX);
}

double Circle::getWidth() const {
    return _rayon;
}

std::string Circle::encode() const {
    return PREFIX + std::to_string(_rayon) + _centre.encode();
}

void Circle::initialize() {
    Figure::registerFigure(Circle::decodable, Circle::decode);
}

double Circle::getHeight() const {
    return _rayon;
}

double Circle::area() const {
    return 3.1416 * _rayon * _rayon;
}

double Circle::perimeter() const {
    return 2. * 3.1416 * _rayon;
}

Figure *Circle::scale(float factor) const {
    return new Circle(this->_centre, this->_rayon * factor);
}

Figure *Circle::rotate(float angle, double center_x, double center_y) const {
    double radianAngle = angle / 180.0 * M_PI;
    long x_new = lround(
            cos(radianAngle) * (_centre.getX() - center_x) - sin(radianAngle) * (_centre.getY() - center_y) + center_x);
    long y_new = lround(
            sin(radianAngle) * (_centre.getX() - center_x) + cos(radianAngle) * (_centre.getY() - center_y) + center_y);
    return new Circle(Point(x_new, y_new), _rayon);
}



















