//
// Created by Pierre Peronnet on 12/04/2016.
//

#ifndef PATCHWORK_PATCHWORK_H
#define PATCHWORK_PATCHWORK_H

#include <string>

bool startWith(std::istream &message, const std::string &prefix);

void initializePatchwork();

void terminatePatchwork();

#endif //PATCHWORK_PATCHWORK_H
