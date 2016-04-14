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

bool startWith(std::istream &message, const std::string prefix) {
    char buffer[100];

    message.get(buffer, prefix.size() + 1);

    return 0 == prefix.compare(0, prefix.size(), buffer);
}