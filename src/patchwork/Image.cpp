//
// Created by Pichou Maxime on 29/03/2016.
//

#include "Image.h"

const std::string Image::PREFIX = std::string("IMG");

Figure *Image::copy() const {


    Image *image = new Image();

    set<Figure *>::const_iterator it(_figures.begin());
    set<Figure *>::const_iterator end(_figures.end());
    while (it != end) {
        image->add(*((*it)->copy()));
        it++;
    }
    return image;
}

void Image::initialize() {
    Figure::registerFigure(Image::decodable, Image::decode);
}

Figure *Image::decode(char **message) {
    Image *image = new Image();
    int nb;

    *message = *message + PREFIX.size();

    std::sscanf(*message, "[%d]", &nb);

    for (; nb > 0; nb--) {
        image->add(*Figure::decode(message));
    }

    return image;
}

std::string Image::encode() const {
    std::string message = PREFIX + "[" + std::to_string(_figures.size()) + "]";

    set<Figure *>::const_iterator it(_figures.begin());
    set<Figure *>::const_iterator end(_figures.end());
    while (it != end) {
        message += (*it)->encode();
        it++;
    }

    return message;
}

bool Image::decodable(char *message) {
    return 0 == PREFIX.compare(0, PREFIX.size(), string(message));
}

void Image::add(const Figure &f) {
    if (f == *this)
        return;

    if (dynamic_cast<const Image *>(&f) != 0) {
        if (area() < f.area()) {
            cout << "Can't add larger image than the current image!" << endl;
            return;
        }
    }

    if (_count == IMAGE_MAX) {
        cerr << "Image is full " << endl;
    }
    else {
        unsigned long tmp_size = _figures.size();
        _figures.insert((const_cast<Figure *> (&f)));
        unsigned long actual_size = _figures.size();
        if (actual_size > tmp_size) {
            _count++;
        }
    }
}

void Image::show(ostream &stream) const {

    stream << "Image contains " << this->_count << "figures" << endl;
}

/*
 * TODO
 */
double Image::getWidth() const {
    return 0;
}

/*
 * TODO
 */
double Image::getHeight() const {
    return 0;
}

/*
 * TODO
 */
Figure *Image::scale(float factor) const {
    return nullptr;
}

/*
 * TODO
 */
double Image::area() const {
    return 0;
}

/*
 * TODO
 */
double Image::perimeter() const {
    return 0;
}

bool operator<(const Figure &left, const Figure &right) {
    return left.getWidth() < right.getWidth() && left.getHeight() < right.getHeight();
}

Figure *Image::rotate(float angle) const {
    return nullptr;
}

int Image::getCount() {
    return _count;
}

Figure *Image::get(int i) const {
    return *std::next(_figures.begin(), i);
}

