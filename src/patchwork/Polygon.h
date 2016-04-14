//
// Created by Pichou Maxime on 14/04/2016.
//

#ifndef PATCHWORK_POLYGON_H
#define PATCHWORK_POLYGON_H

#include <vector>
#include "figure.hpp"

class Polygon : public Figure {
public:
    Polygon()
            : _points() { }

    Figure *copy() const;

    static Figure *decode(char **message);

    std::string encode() const;

    static bool decodable(char *message);

    void show(ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    Figure *scale(float factor) const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle, double center_x, double center_y) const;

    static void initialize();

    void addPoint(const Point &p);

private:
    static const std::string PREFIX;
    vector<Point *> _points;
};


#endif //PATCHWORK_POLYGON_H
