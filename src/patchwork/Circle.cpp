//
// Created by Pichou Maxime on 29/03/2016.
//

#include <math.h>
#include "Circle.h"

const std::string Circle::PREFIX = std::string("CIRC");

/**
 * Fonction virtuelle de copie
 */
Figure *Circle::copy() const {
    return new Circle(this->_centre, this->_rayon);
}

void Circle::show(std::ostream &stream) const {
    stream << "Circle(Center:" << _centre << ", Radius;" << _rayon << ")";
}

Figure *Circle::decode(std::istream &message) {
    double rayon;
    char buffer[100];
    Point *center;

    message.get(buffer, PREFIX.size() + strlen(":"));
    message >> rayon;
    center = Point::decode(message);

    return new Circle(*center, rayon);
}

bool Circle::decodable(std::istream &message) {
    char buffer[100];
    message.get(buffer, PREFIX.size());
    return 0 == PREFIX.compare(0, PREFIX.size(), buffer);
}

double Circle::getWidth() const {
    return _rayon;
}

std::string Circle::encode() const {
    return PREFIX + ":" + std::to_string(_rayon) + _centre.encode();
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



















