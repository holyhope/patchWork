//
// Created by Pierre Peronnet on 12/04/2016.
//

#include <clocale>

#include "Line.h"
#include "Circle.h"
#include "Image.h"
#include "Rectangle.h"
#include "Polygon.h"

#define BUFFER_SIZE 100

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

bool startWith(std::istream &message, const std::string &prefix) {
    char buffer[BUFFER_SIZE];

    message.get(buffer, prefix.size() + 1);

    return 0 == prefix.compare(0, prefix.size(), buffer);
}