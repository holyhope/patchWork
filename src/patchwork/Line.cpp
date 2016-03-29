//
// Created by Pichou Maxime on 29/03/2016.
//

#include "Line.h"

Figure *Line::copy() const {
    return new Line(this->_origin, this->_extremity);
}

void Line::show(ostream &stream) const {
    stream << "Line((" << this->_origin << ")(" << this->_extremity << ")" << endl;
}

/*
 * TODO
 */
double Line::getWidth() const {
    return 0;
}

/*
 * TODO
 */
double Line::getHeight() const {
    return 0;
}

/*
 * TODO
 */
Figure *Line::scale(float factor) const {
    return nullptr;
}

/*
 * TODO
 */
double Line::area() const {
    return 0;
}

/*
 * TODO
 */
double Line::perimeter() const {
    return 0;
}













