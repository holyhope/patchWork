//
// Created by Pierre Peronnet on 13/04/2016.
//

#include <iostream>
#include "figure.hpp"

FigureList *registeredFigures = NULL;

ostream &operator<<(ostream &os, const Figure &figure) {
    os << "Undefined figure";
    return os;
}

bool Figure::operator==(const Figure &f) const {
    return (this == &f);
}

std::string Figure::encode(Figure &figure) {
    return figure.encode();
}

Figure *Figure::decode(char **message) {
    FigureList *list;

    for (list = registeredFigures; list != NULL; list = list->next) {
        if (list->decodable(*message)) {
            return list->decode(message);
        }
    }

    throw new std::runtime_error("Figure is not registrered");
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