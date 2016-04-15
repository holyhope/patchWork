#ifndef PATCHWORK_FIGURE_HPP
#define PATCHWORK_FIGURE_HPP

/**
 * \file figure.hpp
 * \brief Virtual class of a figure
 */
#include <iostream>
#include "point.hpp"

class Figure;

typedef Figure *decodeMethod(std::istream &msg);

typedef bool decodableMethod(std::istream &msg);

class Figure {

public:

    /**
     * Copy this figure and return a new one.
     * \return the copy of this figure.
     */
    virtual Figure *copy() const = 0;

    /**
     * Destroy the figure.
     */
    virtual ~Figure() { };


    /**
     *  Display the figure in the standard output in formatted string representation.
     * \param stream output to display the figure.
     */
    virtual void show(std::ostream &stream) const = 0;

    /**
     * Method use to decode a a figure encoded in string type.
     * \param message the figure represented as string.
     * \return the Figure decoded.
     */
    static Figure *decode(std::istream &message);

    static void registerFigure(decodableMethod *decodable, decodeMethod *decode);

    static void clearRegisteredFigures();

    /**
     * Get width of the figure.
     * \return the width of the figure as double.
     */
    virtual double getWidth() const = 0;

    /**
     * Get height of the figure.
     * \return the height of the figure as double.
     */
    virtual double getHeight() const = 0;

    /**
     * Construct a new rotated figure.
     * \param angle angle to rotate figure in degrees.
     * \param center_x coordinate X of the rotation point.
     * \param center_y coordinate Y of the rotation point.
     * \return a new figure with the rotation performed.
     */
    virtual Figure *rotate(float angle, double center_x, double center_y) const = 0;

    /**
     * Construct a new translated figure.
     * \param p translated point.
     * \return a new figure with the translation performed.
     */
    virtual Figure *translate(Point p) const = 0;

    /**
     * Get the area of the figure.
     * \return the area of the figure.
     */
    virtual double area() const = 0;

    /**
     * Get the length of the perimeter.
     * \return the perimeter of the figure.
     */
    virtual double perimeter() const = 0;

    bool operator==(const Figure &f) const;

    friend std::ostream &operator<<(std::ostream &os, const Figure &f);

    /**
     * Encode a figure to be sent to the server
     * \return a string representation of the figure
     */
    virtual std::string encode() const = 0;
};

#endif
