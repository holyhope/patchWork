//
// Created by Pierre Peronnet on 13/04/2016.
//

#include <iostream>
#include "figure.hpp"

typedef struct _figureList {
    decodeMethod *decode;

    decodableMethod *decodable;

    struct _figureList *next;
} FigureList;

FigureList *registeredFigures = NULL;

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