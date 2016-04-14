//
// Created by Pierre Peronnet on 13/04/2016.
//

#include <iostream>
#include <string>
#include "figure.hpp"

typedef struct _figureList {
    decodeMethod *decode;

    decodableMethod *decodable;

    struct _figureList *next;
} FigureList;

FigureList *registeredFigures = NULL;

std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    os << "Undefined figure";
    return os;
}

bool Figure::operator==(const Figure &f) const {
    return (this == &f);
}

std::string Figure::encode(Figure &figure) {
    return figure.encode();
}

Figure *Figure::decode(std::istream &message) {
    std::fpos<mbstate_t> pos;
    FigureList *list;
    bool decodable;

    for (list = registeredFigures; list != NULL; list = list->next) {
        pos = message.tellg();
        decodable = list->decodable(message);
        message.seekg(pos);
        if (decodable) {
            return list->decode(message);
        }
    }

    throw std::invalid_argument("No figure found");
}

void Figure::registerFigure(decodableMethod *decodable, decodeMethod *decode) {
    FigureList *list = new FigureList();

    list->decode = decode;
    list->decodable = decodable;
    list->next = registeredFigures;
    registeredFigures = list;
}

void Figure::clearRegisteredFigures() {
    FigureList *list;

    while ((list = registeredFigures) != NULL) {
        registeredFigures = list->next;
        free(list);
    }

    registeredFigures = NULL;
}