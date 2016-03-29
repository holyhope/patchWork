//
// Created by Pichou Maxime on 29/03/2016.
//

#include "Image.h"

Figure *Image::copy() const {


        Image * image = new Image();

        list<Figure *>::const_iterator it(_figures.begin());
        list<Figure *>::const_iterator end(_figures.end());
        while(it != end)
        {
            image->add(*((*it)->copy()));
            it++;
        }
        return image;

}

void Image::add(const Figure &f) {
    if (f == *this)
        return;

    if (dynamic_cast<const Image *>(&f) != 0)
    {
        if (area() < f.area())
        {
            cout << "Can't add larger image than the current image!" << endl;
            return;
        }
    }

    if (_count == IMAGE_MAX)
    {
        cerr << "Image is full " << endl;
    }
    else
    {
        _figures.push_back((const_cast<Figure *> (&f))->copy());
        _count++;
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















