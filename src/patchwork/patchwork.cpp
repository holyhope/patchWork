#include <clocale>

#include "Line.h"
#include "Circle.h"
#include "Image.h"
#include "Rectangle.h"
#include "Polygon.h"

void initializePatchwork() {
    std::setlocale(LC_ALL, "en_US.utf8");

    Line::initialize();
    Image::initialize();
    Circle::initialize();
    Polygon::initialize();
    Rectangle::initialize();
}

void terminatePatchwork() {
    Figure::clearRegisteredFigures();
}