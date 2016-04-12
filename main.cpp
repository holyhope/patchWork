#include <iostream>
#include "src/patchwork/Circle.h"
#include "src/patchwork/Rectangle.h"
#include "src/patchwork/Image.h"
#include "src/patchwork/Line.h"

using namespace std;

int main() {
    Circle circle(Point(0, 0), 3.);
    cout << circle << endl;
    cout << "Area: " << circle.area() << " Perimeter: " << circle.perimeter() << endl;


    Circle *circleMinus = (Circle *) circle.scale(0.5);
    cout << *circleMinus << endl;
    cout << "AreaMinus: " << circleMinus->area() << endl;


    Rectangle rectangle(Point(-2, -3), Point(2, 4));
    cout << "RECTANGLE : " << rectangle << endl;
    cout << "Width : " << rectangle.getWidth() << " Height " << rectangle.getHeight() << endl;
    cout << "Area: " << rectangle.area() << " Perimeter: " << rectangle.perimeter() << endl;

    Line line(Point(1,4), Point(6,1));
    cout << "LINE : "<< line << endl;
    cout << "Width : " << line.getWidth() << " Height " << line.getHeight() << endl;
    cout << "Area: " << line.area() << " Perimeter: " << line.perimeter() << endl;
    Line *line2 = (Line*) line.scale(-3.);
    cout << "NEW SCALING LINE : "<< *line2 << endl;
    cout << "Width : " << line2->getWidth() << " Height " << line2->getHeight() << endl;
    cout << "Area: " << line2->area() << " Perimeter: " << line2->perimeter() << endl;

    Line *line3 = (Line*) line.rotate(90);
    cout << "NEW ROTATE LINE : "<< *line3 << endl;
    cout << "Width : " << line3->getWidth() << " Height " << line3->getHeight() << endl;
    cout << "Area: " << line3->area() << " Perimeter: " << line3->perimeter() << endl;

    Image image(Point(0, 0));
    image.add(circle);
    cout << image << endl; // display 1

    image.add(rectangle);
    image.add(rectangle); // do anything cause std::set can't contain duplicate value
    cout << image << endl; // display 2 and not 3

    image.~Image();
    cout << "remove done" << endl;
    cout << image << endl; //display 0
    return 0;
}