//
// Created by Pichou Maxime on 29/03/2016.
//

#include <string.h>
#include "Image.h"
#include "common.h"

const std::string Image::PREFIX = std::string("IMG");

Figure *Image::copy() const {
    Image *image = new Image();

    std::set<Figure *>::const_iterator it(_figures.begin());
    std::set<Figure *>::const_iterator end(_figures.end());
    while (it != end) {
        image->add(*((*it)->copy()));
        it++;
    }

    return image;
}

Image::Image(const Image &image) :
        _origin(image._origin), _figures(), _count(0) {
    std::set<Figure *>::const_iterator it(image._figures.begin());
    std::set<Figure *>::const_iterator end(image._figures.end());
    while (it != end) {
        add(*((*it)->copy()));
        ++it;
    }
}

void Image::initialize() {
    Figure::registerFigure(Image::decodable, Image::decode);
}

Figure *Image::decode(std::istream &stream) {
    Image *image = new Image();
    int nb;

    stream.ignore(PREFIX.size());
    stream >> nb;

    if (!stream.good()) {
        throw std::invalid_argument("Not an image");
    }

    for (; nb > 0; nb--) {
        image->add(*Figure::decode(stream));
    }

    return image;
}

std::string Image::encode() const {
    std::string message = PREFIX + std::to_string(getCount());

    std::set<Figure *>::const_iterator it(_figures.begin());
    std::set<Figure *>::const_iterator end(_figures.end());
    while (it != end) {
        message += (*it)->encode();
        it++;
    }

    return message;
}

bool Image::decodable(std::istream &message) {
    return startWith(message, PREFIX);
}

void Image::add(const Figure &f) {
    if (f == *this)
        return;

    if (_count == IMAGE_MAX) {
        std::cerr << "Image is full " << std::endl;
    } else {
        unsigned long tmp_size = _figures.size();
        _figures.insert((const_cast<Figure *> (&f)));
        unsigned long actual_size = _figures.size();
        if (actual_size > tmp_size) {
            _count++;
        }
    }
}

void Image::show(std::ostream &stream) const {
    static int depth = 0;

    if (0 == _count) {
        stream << "Empty image";
        return;
    }

    stream << "Image contains " << _count << " figure" << (_count > 1 ? "s" : "") << std::endl;
    depth++;

    std::set<Figure *>::const_iterator it(_figures.begin());
    std::set<Figure *>::const_iterator end(_figures.end());
    while (it != end) {
        for (int i = 0; i < depth; i++) {
            stream << ">";
        }
        stream << " " << **it;
        it++;
        if (it != end) {
            stream << std::endl;
        }
    }

    depth--;
}

double Image::getWidth() const {
    double maxWidth = 0;
    for (auto f : _figures) {
        if (f->getWidth() > maxWidth) {
            maxWidth = f->getWidth();
        }
    }
    return maxWidth;
}


double Image::getHeight() const {
    double maxHeight = 0;
    for (auto f : _figures) {
        if (f->getHeight() > maxHeight) {
            maxHeight = f->getHeight();
        }
    }
    return maxHeight;
}

Figure *Image::scale(float factor) const {
    Image *newImage = new Image(this->_origin);
    for (auto f : _figures) {
        newImage->add(*f->scale(factor));
    }
    return newImage;
}

double Image::area() const {
    double totalArea = 0;
    for (auto f : _figures) {
        totalArea += f->area();
    }
    return totalArea;
}

double Image::perimeter() const {
    double totalPerimeter = 0;
    for (auto f : _figures) {
        totalPerimeter += f->perimeter();
    }
    return totalPerimeter;
}

bool operator<(const Figure &left, const Figure &right) {
    return left.getWidth() < right.getWidth() && left.getHeight() < right.getHeight();
}

Figure *Image::rotate(float angle, double center_x, double center_y) const {
    Image *newImage = new Image(this->_origin);
    for (auto f : _figures) {
        newImage->add(*f->rotate(angle, center_x, center_y));
    }
    return newImage;
}

int Image::getCount() const {
    return _count;
}

Figure *Image::get(int i) const {
    if (i >= 0 && i < _count) {
        return *std::next(_figures.begin(), i);
    }
    return 0;

}

