#ifndef PATCHWORK_FIGURE_HPP
#define PATCHWORK_FIGURE_HPP

#include <iostream>
#include "point.h"

typedef char* color;

using namespace std;

class Figure {

public:

    virtual Figure * copy() const = 0;

    virtual ~Figure() { };

	/**
	 * Draw figure in window.
	 */
	//virtual void draw() const = 0;

	/**
	 * Display an ASCII figure on the output stream.
	 */
	virtual void show(ostream &stream) const = 0;

	/**
	 * Get the color of the figure.
	 */
	virtual color getColor() const {
        return _color;
    }

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
	virtual Figure* rotate(float angle) const = 0;
	
	/**
	 * Construct a new translated figure.
	 */
	//virtual Figure* translate(Point p) const = 0;
	
	/**
	 * Construct a new scaled figure.
	 */
	virtual Figure* scale(float factor) const = 0;

	/**
	 * Construct a new scaled and translated figure.
	 */
	//virtual Figure* homothety(Point p, float factor) const = 0 ;

	/**
	 * Construct a new symetrical figure.
	 */
	//virtual Figure* axialSymetry() const = 0;

	/**
	 * Construct a new symatrical figure.
	 */
	//virtual Figure* centralSymetry() const = 0;

	/**
	 * Construct a new colorized figure.
	 */
	//virtual Figure* colorize() const = 0;

	/**
	 * get the area
	 */
	virtual double area()  const = 0;

	/**
	 * Get the length of the perimeter.
	 */
	virtual double perimeter() const = 0;

    bool operator==(const Figure &f) const {
        return (this == &f);
    }

    friend ostream & operator<< (ostream & os, const Figure & figure)
    {
        figure.show(os);
        return os;
    }

private:
    color _color;
};

#endif
