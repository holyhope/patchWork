#ifndef PATCHWORK_IMAGE_H
#define PATCHWORK_IMAGE_H

/**
 * \file Image.h
 * \brief Representation of an Image, inherited from Figure class. Can contains all Figures.
 */

#include <list>
#include <set>
#include <iostream>
#include "figure.hpp"
#include "point.hpp"

class Image : public Figure {

public:

    enum {
        IMAGE_MAX = 50
    };

    /**
     * Constructor of Image class.
     * \param a the top-left corner point of the image.
     */
    Image(const Point &a = Point(0, 0))
            : _origin(a), _figures(), _count(0) { }

    Image(const Image &image);

    /**
     * Add a new Figure into this image.
     * \param f the figure to add to this image.
     */
    void add(const Figure &f);

    /**
     * Remove a figure from this image.
     * \param f the figure to remove.
     */
    void remove(const Figure &f);

    Figure *copy() const;

    ~Image() {

        std::set<Figure *>::iterator it(_figures.begin());
        std::set<Figure *>::iterator tmp;

        for (; it != _figures.end();) {
            tmp = it;
            ++tmp;
            _figures.erase(it);
            _count--;
            it = tmp;

        }
    }

    static Figure *decode(std::istream &message);

    std::string encode() const;

    static bool decodable(std::istream &message);

    void show(std::ostream &stream) const;

    double getWidth() const;

    double getHeight() const;

    Figure *translate(Point p) const;

    double area() const;

    double perimeter() const;

    Figure *rotate(float angle, double center_x, double center_y) const;

    friend bool operator<(const Figure &left, const Figure &right);

    static void initialize();

    /**
     * get the number of figure in this image.
     * \return the number of figure.
     */
    int getCount() const;

    /**
     * Get a figure with an index.
     * \param i index of Image.
     * \return the i th figure of this image.
     */
    Figure *get(int i) const;

private:
    static const std::string PREFIX;
    Point _origin;

    std::set<Figure *> _figures;

    int _count;
};

#endif //PATCHWORK_IMAGE_H
