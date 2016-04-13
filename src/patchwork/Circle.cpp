//
// Created by Pichou Maxime on 29/03/2016.
//

#include "Circle.h"

const std::string Circle::PREFIX = std::string("CIRC");

/**
 * Fonction virtuelle de copie
 */
Figure *Circle::copy() const {
    return new Circle(this->_centre, this->_rayon);
}

void Circle::show(ostream &stream) const {
    stream << "Circle(Center:" << _centre << ", Radius;" << _rayon << ")";
}

Figure *Circle::decode(char **message) {
    int rayon;
    Point *center;
    *message = *message + PREFIX.size();
    center = Point::decode(message);
    std::sscanf(*message, ":%d", &rayon);
    return new Circle(*center, rayon);
}

bool Circle::decodable(char *message) {
    return 0 == PREFIX.compare(0, PREFIX.size(), string(message));
}

double Circle::getWidth() const {
    return _rayon;
}

std::string Circle::encode() const {
    return PREFIX + _centre.encode() + ":" + std::to_string(_rayon);
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

Figure *Circle::rotate(float angle) const {
    return nullptr;
}















