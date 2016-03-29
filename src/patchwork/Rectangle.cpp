//
// Created by Pichou Maxime on 29/03/2016.
//

#include "Rectangle.h"

Figure *Rectangle::copy() const {
    return new Rectangle(this->_origin, this->_extremity);
}

void Rectangle::show(ostream &stream) const {
    stream << "Origin(" << this->_origin << ") Extremity(" << this->_extremity << ")"<< endl;
}

double Rectangle::getWidth() const {
    return this->_extremity.getX() - this->_origin.getX();
}

double Rectangle::getHeight() const {
    return this->_extremity.getY() - this->_origin.getY();
}

/*
 * TODO
 */
Figure *Rectangle::scale(float factor) const {
    return nullptr;
}

double Rectangle::area() const {
    return getWidth()*getHeight();
}

double Rectangle::perimeter() const {
    return 2*getWidth() + 2*getHeight();
}













