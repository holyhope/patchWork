#ifndef PATCHWORK_FIGURE_HPP
#define PATCHWORK_FIGURE_HPP

#include <iostream>
#include "point.hpp"

class Figure;

typedef Figure *decodeMethod(std::istream &msg);

typedef bool decodableMethod(std::istream &msg);

class Figure {

public:

    virtual Figure *copy() const = 0;

    virtual ~Figure() { };

    /**
     * Draw figure in window.
     */
    //virtual void draw() const = 0;

    /**
     * Display an ASCII figure on the output stream.
     */
    virtual void show(std::ostream &stream) const = 0;

    static Figure *decode(std::istream &message);

    static void registerFigure(decodableMethod *decodable, decodeMethod *decode);

    static void clearRegisteredFigures();

    /**
     * Get width of the figure.
     */
    virtual double getWidth() const = 0;

    /**
     * Get height of the figure.
     */
    virtual double getHeight() const = 0;

    /**
     * Construct a new rotated figure.
     */
    virtual Figure *rotate(float angle, double center_x, double center_y) const = 0;

    /**
     * Construct a new translated figure.
     */
    virtual Figure *translate(Point p) const = 0;

    /**
     * Construct a new scaled figure.
     */
    virtual Figure *scale(float factor) const = 0;

    /**
     * get the area
     */
    virtual double area() const = 0;

    /**
     * Get the length of the perimeter.
     */
    virtual double perimeter() const = 0;

    bool operator==(const Figure &f) const;

    friend std::ostream &operator<<(std::ostream &os, const Figure &f);

    virtual std::string encode() const = 0;
};

#endif
