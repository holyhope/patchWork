#ifndef PATCHWORK_FIGURE_HPP
#define PATCHWORK_FIGURE_HPP

#include <iostream>

typedef char* color;
typedef struct {
	int x;
	int y;
} point, vector;

using namespace std;

class figure {
private:
	color _color;

public:
	/**
	 * Constructor
	 */
	figure(color col): _color(col) {
	}

	/**
	 * Draw figure in window.
	 */
	void draw(void *);

	/**
	 * Display an ASCII figure on the output stream.
	 */
	void show(ostream &stream);

	/**
	 * Get the color of the figure.
	 */
	color getColor();

	/**
	 * Get the top left corner of the smallest rectangle containing the figure.
	 */
	point getPosition();

	/**
	 * Get width of the figure.
	 */
	int getWidth();

	/**
	 * Get height of the figure.
	 */
	int getHeight();

	/**
	 * Construct a new rotated figure.
	 */
	figure* rotate(float angle);
	
	/**
	 * Construct a new translated figure.
	 */
	figure* translate(vector vec);
	
	/**
	 * Construct a new scaled figure.
	 */
	figure* scale(float factor);

	/**
	 * Construct a new scaled and translated figure.
	 */
	figure* homothety(vector vec, float factor) {
		return this->translate(vec)->scale(factor);
	}

	/**
	 * Construct a new symetrical figure.
	 */
	figure* axialSymetry();

	/**
	 * Construct a new symatrical figure.
	 */
	figure* centralSymetry();

	/**
	 * Construct a new colorized figure.
	 */
	figure* colorize();

	/**
	 * get the area
	 */
	int area();

	/**
	 * Get the length of the perimeter.
	 */
	int perimeter();
};

#endif
