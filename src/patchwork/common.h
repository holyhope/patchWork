//
// Created by Pierre Peronnet on 14/04/2016.
//

#ifndef PATCHWORK_COMMON_H
#define PATCHWORK_COMMON_H

#include <string>

static const char *const PUT_ACTION = "PUT";
static const char *const GET_ACTION = "GET";

bool startWith(std::istream &message, const std::string &prefix);

#endif //PATCHWORK_COMMON_H
