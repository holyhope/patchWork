//
// Created by Pichou Maxime on 29/03/2016.
//

#include "Circle.h"

/**
 * Fonction virtuelle de copie
 */
Figure *Circle::copy() const {
    return new Circle(this->_centre, this->_rayon);
}

void Circle::show(ostream &stream) const {
    stream << "          *****         \n"
    << "       *         *      \n"
    << "      *            *    \n"
    << "     *              *   \n"
    << "     *              *   \n"
    << "     *              *   \n"
    << "     *              *   \n"
    << "      *            *    \n"
    << "        *        *      \n"
    << "           *****         \n"
    << endl;
    stream << "cercle : (" << _centre << ", " << _rayon << ")" << endl;
}

double Circle::getWidth() const {
    return _rayon;
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















