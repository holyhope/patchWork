#include <cmath>
#include "Rectangle.h"
#include "common.h"

const std::string Rectangle::PREFIX = std::string("RECT");

Figure *Rectangle::copy() const {
    return new Rectangle(this->_origin, this->_extremity);
}

Figure *Rectangle::decode(std::istream &message) {
    Point *origin, *extremity;

    message.ignore(PREFIX.size());
    origin = Point::decode(message);
    extremity = Point::decode(message);

    return new Rectangle(*origin, *extremity);
}

void Rectangle::initialize() {
    Figure::registerFigure(Rectangle::decodable, Rectangle::decode);
}

std::string Rectangle::encode() const {
    return PREFIX + _origin.encode() + _extremity.encode();
}

bool Rectangle::decodable(std::istream &message) {
    return startWith(message, PREFIX);
}

void Rectangle::show(std::ostream &stream) const {
    stream << "Rectangle(Origin:" << this->_origin << ", Extremity:" << this->_extremity << ")";
}

double Rectangle::getWidth() const {
    Point C(_extremity.getX(), _origin.getY());

    double xC_minus_xOrigin = C.getX() - _origin.getX();
    double yC_minus_yOrigin = C.getY() - _origin.getY();

    return sqrt((xC_minus_xOrigin * xC_minus_xOrigin) + (yC_minus_yOrigin * yC_minus_yOrigin));
}

double Rectangle::getHeight() const {
    Point C(_extremity.getX(), _origin.getY());

    double xC_minus_xExtremity = C.getX() - _extremity.getX();
    double yC_minus_yExtremity = C.getY() - _extremity.getY();

    return sqrt((xC_minus_xExtremity * xC_minus_xExtremity) + (yC_minus_yExtremity * yC_minus_yExtremity));
}

double Rectangle::area() const {
    return getWidth() * getHeight();
}

double Rectangle::perimeter() const {
    return 2 * getWidth() + 2 * getHeight();
}

Figure *Rectangle::rotate(float angle, double center_x, double center_y) const {
    double radianAngle = angle / 180.0 * M_PI;
    center_x = (_origin.getX() + _extremity.getX()) / 2.;
    center_y = (_origin.getY() + _extremity.getY()) / 2.;

    long Ax_new = lround(
            cos(radianAngle) * (_origin.getX() - center_x) - sin(radianAngle) * (_origin.getY() - center_y) + center_x);
    long Ay_new = lround(
            sin(radianAngle) * (_origin.getX() - center_x) + cos(radianAngle) * (_origin.getY() - center_y) + center_y);

    long Bx_new = lround(
            cos(radianAngle) * (_extremity.getX() - center_x) - sin(radianAngle) * (_extremity.getY() - center_y) +
            center_x);
    long By_new = lround(
            sin(radianAngle) * (_extremity.getX() - center_x) + cos(radianAngle) * (_extremity.getY() - center_y) +
            center_y);

    return new Rectangle(Point(Ax_new, Ay_new), Point(Bx_new, By_new));
}

bool Rectangle::operator==(const Rectangle &r) const {
    return _origin == r._origin && _extremity == r._extremity;
}

Figure *Rectangle::translate(Point p) const {
    return new Rectangle(Point(_origin.getX() + p.getX(), _origin.getY() + p.getY()),
                         Point(_extremity.getX() + p.getX(), _extremity.getY() + p.getY()));
}
