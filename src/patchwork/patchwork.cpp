//
// Created by Pierre Peronnet on 12/04/2016.
//

#include <clocale>

#include "Line.h"
#include "Circle.h"
#include "Image.h"
#include "Rectangle.h"

void initializePatchwork() {
    std::setlocale(LC_ALL, "en_US.utf8");

    Line::initialize();
    Circle::initialize();
    Image::initialize();
    Rectangle::initialize();
}

void terminatePatchwork() {
    Figure::clearRegisteredFigures();
}