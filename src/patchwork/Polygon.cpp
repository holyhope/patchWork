//
// Created by Pichou Maxime on 14/04/2016.
//

#include <set>
#include <cmath>
#include "Polygon.h"
#include "patchwork.h"

const std::string Polygon::PREFIX = std::string("POLY");

Figure *Polygon::copy() const {
    Polygon *poly = new Polygon();

    std::vector<Point *>::const_iterator it(_points.begin());
    std::vector<Point *>::const_iterator end(_points.end());
    while (it != end) {
        poly->addPoint(Point((*it)->getX(), (*it)->getY()));
        it++;
    }
    return poly;
}

Figure *Polygon::decode(std::istream &message) {
    Polygon *poly = new Polygon();
    int size;

    message.ignore(PREFIX.size());
    message >> size;

    for (int i = 0; i < size; i++) {
        Point *x;
        x = Point::decode(message);
        poly->addPoint(*x);
    }

    return poly;
}

std::string Polygon::encode() const {
    std::string encodePolygon = PREFIX + std::to_string(_points.size());
    for (auto p : _points) {
        encodePolygon += p->encode() + " ";
    }
    return encodePolygon;
}

bool Polygon::decodable(std::istream &message) {
    return startWith(message, PREFIX);
}

void Polygon::show(std::ostream &stream) const {
    stream << "Polygon(";
    for (Point *p : _points) {
        stream << "(" << p->getX() << ", " << p->getY() << "), ";
    }
    stream << ")";
}

double Polygon::getWidth() const {
    int minX = 100,
            maxX = 0;

    for (auto p : _points) {
        if (p->getX() < minX) {
            minX = p->getX();
        }
        if (p->getX() > maxX) {
            maxX = p->getX();
        }
    }
    return maxX - minX;

}

double Polygon::getHeight() const {
    int minY = 100,
            maxY = 0;
    for (auto p : _points) {
        if (p->getY() < minY) {
            minY = p->getY();
        }
        if (p->getY() > maxY) {
            maxY = p->getY();
        }
    }
    return maxY - minY;
}

/*
 * TODO
 */
Figure *Polygon::scale(float factor) const {
    return nullptr;
}

double Polygon::area() const {
    int sum1 = 0;
    int sum2 = 0;
    for (std::vector<Point *>::const_iterator it = _points.begin(); it != (_points.end() - 1); ++it) {
        sum1 += (*it)->getX() + (*it + 1)->getY();
        sum2 += (*it)->getY() + (*it + 1)->getX();
    }
    sum1 += _points.at(_points.size() - 1)->getX() + _points.at(0)->getY();
    sum2 += _points.at(_points.size() - 1)->getY() + _points.at(0)->getX();
    return abs((sum2 - sum1)) / 2.;
}


double Polygon::perimeter() const {
    double perimeter = 0;
    for (std::vector<Point *>::const_iterator it = _points.begin(); it != (_points.end() - 1); ++it) {
        int xA = (*it)->getX();
        int yA = (*it)->getY();
        int xB = (*it + 1)->getX();
        int yB = (*it + 1)->getY();
        perimeter += sqrt((xB - xA) * (xB - xA) + (yB - yA) * (yB - yA));
    }
    int xA = _points.at(_points.size() - 1)->getX();
    int yA = _points.at(_points.size() - 1)->getY();
    int xB = _points.at(0)->getX();
    int yB = _points.at(0)->getY();
    perimeter += sqrt((xB - xA) * (xB - xA) + (yB - yA) * (yB - yA));
    return perimeter;
}


Figure *Polygon::rotate(float angle, double center_x, double center_y) const {
    double radianAngle = angle / 180.0 * M_PI;
    Polygon *poly = new Polygon();
    for (std::vector<Point *>::const_iterator it = _points.begin(); it != (_points.end()); ++it) {
        long x_new = lround(
                cos(radianAngle) * ((*it)->getX() - center_x) - sin(radianAngle) * ((*it)->getY() - center_y) +
                center_x);
        long y_new = lround(
                sin(radianAngle) * ((*it)->getX() - center_x) + cos(radianAngle) * ((*it)->getY() - center_y) +
                center_y);

        poly->addPoint(Point(x_new, y_new));
    }
    return poly;
}

void Polygon::initialize() {
    Figure::registerFigure(Polygon::decodable, Polygon::decode);
}

void Polygon::addPoint(const Point &p) {
    _points.push_back((const_cast<Point *> (&p)));
}



