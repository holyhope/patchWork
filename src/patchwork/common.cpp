//
// Created by Pierre Peronnet on 14/04/2016.
//

#include <string>
#include <iostream>

#define BUFFER_SIZE 100

bool startWith(std::istream &message, const std::string &prefix) {
    char buffer[BUFFER_SIZE];

    message.get(buffer, prefix.size() + 1);

    return 0 == prefix.compare(0, prefix.size(), buffer);
}