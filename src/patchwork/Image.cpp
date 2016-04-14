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

Image::Image(const Image &image) :
        _origin(image._origin), _figures(), _count(0) {
    set<Figure *>::const_iterator it(image._figures.begin());
    set<Figure *>::const_iterator end(image._figures.end());
    while (it != end) {
        add(*((*it)->copy()));
        ++it;
    }
}

void Image::initialize() {
    Figure::registerFigure(Image::decodable, Image::decode);
}

std::ostream &operator<<(std::ostream &os, const Image &image) {
    image.show(os);
    return os;
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

int Image::getCount() {
    return _count;
}

Figure *Image::get(int i) const {
    if (i >= 0 && i < _count) {
        return *std::next(_figures.begin(), i);
    }
    return 0;

}

