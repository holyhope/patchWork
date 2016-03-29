#include <iostream>
#include "src/patchwork/Circle.h"
#include "src/patchwork/Rectangle.h"
#include "src/patchwork/Image.h"

using namespace std;

int main() {
    Circle circle(Point(0,0), 3.);
    cout << circle << endl;
    cout << "Area: " << circle.area() << " Perimeter: " << circle.perimeter() << endl;
    Circle* circleMinus = (Circle*)circle.scale(0.5);
    cout << *circleMinus << endl;
    cout << "AreaMinus: " << circleMinus->area() << endl;

    Rectangle rectangle(Point(-2,-3), Point(2,4));
    cout << rectangle << endl;
    cout << "Area: " << rectangle.area() << " Perimeter: " << rectangle.perimeter() << endl;

    Image image(Point(0,0));
    image.add(circle);
    cout << image << endl;
    image.add(rectangle);
    cout << image << endl;
    return 0;
}