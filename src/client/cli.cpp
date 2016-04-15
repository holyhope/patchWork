#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <readline/history.h>
#include <vector>

#include "client.h"
#include "../patchwork/Circle.h"
#include "../patchwork/Rectangle.h"
#include "../patchwork/Line.h"
#include "../patchwork/Polygon.h"

typedef enum {
    EXIT,           //0
    DRAW_IMAGE,     //1
    DRAW_LINE,      //2
    DRAW_CIRCLE,    //3
    DRAW_RECTANGLE, //4
    DRAW_POLYGON,   //5
    ROTATE,         //6
    TRANSLATE,      //7
    CLEAR,          //8
    SEND,           //9
    RECEIVE,        //10
    EXPORT,         //11
    IMPORT          //12
} Choice;


using namespace std;

Choice toChoice(const int input) {
    return (Choice) input;
}

template<typename Type>
bool isValidChoice(Type choice, int boundM, int boundP, string errorMessage);

Choice nextChoice(const Image &image) {
    int maxChoice = 0;
    char *input;
    int choice_user;

    do {
        cout << endl << "   **** Draw ****" << endl;
        cout << to_string(++maxChoice) << ".  Draw an image" << endl;
        cout << to_string(++maxChoice) << ".  Draw a Line" << endl;
        cout << to_string(++maxChoice) << ".  Draw a Circle" << endl;
        cout << to_string(++maxChoice) << ".  Draw a Rectangle" << endl;
        cout << to_string(++maxChoice) << ".  Draw a Polygon" << endl;
        cout << endl << "   **** Operation ****" << endl;
        cout << to_string(++maxChoice) << ".  Perform a rotation" << endl;
        cout << to_string(++maxChoice) << ".  Perform a translation" << endl;
        cout << endl << "   **** Other ****" << endl;
        cout << to_string(++maxChoice) << ".  Clear local image" << endl;
        cout << to_string(++maxChoice) << ". Send to server" << endl;
        cout << to_string(++maxChoice) << ". Get from server" << endl;
        cout << to_string(++maxChoice) << ". Export to export.txt" << endl;
        cout << to_string(++maxChoice) << ". Import from import.txt" << endl;
        cout << "0.  Exit this awesome application" << endl;
        cout << endl << image << endl;
        cout << "Your choice : ";

        input = readline("");
        try {
            choice_user = std::atoi(input);
        } catch (const std::invalid_argument &e) {
            // Nothing to do
        }
    } while (!isValidChoice(choice_user, 0, maxChoice + 1, "Please, choose a correct choice."));

    add_history(input);

    return toChoice(choice_user);
}

void askCoordinate(int &pointX1, string whichCoord);

void showImageWithIndex(Image image);

Image *createImage();

Line *createLine();

Circle *createCircle();

Rectangle *createRectangle();

Polygon *createPolygon();

Image *createImage();

Line *createLine();

Circle *createCircle();

Rectangle *createRectangle();

Polygon *createPolygon();

void test1() {
    Circle circle(Point(0, 0), 3.);
    cout << circle << endl;
    cout << "Area: " << circle.area() << " Perimeter: " << circle.perimeter() << endl;


    Rectangle rectangle(Point(-2, -3), Point(2, 4));
    cout << "RECTANGLE : " << rectangle << endl;
    cout << "Width : " << rectangle.getWidth() << " Height " << rectangle.getHeight() << endl;
    cout << "Area: " << rectangle.area() << " Perimeter: " << rectangle.perimeter() << endl;

    Line line(Point(1, 4), Point(6, 1));
    cout << "LINE : " << line << endl;
    cout << "Width : " << line.getWidth() << " Height " << line.getHeight() << endl;
    cout << "Area: " << line.area() << " Perimeter: " << line.perimeter() << endl;


    Line *line3 = (Line *) line.rotate(90, 0, 0);
    cout << "NEW ROTATE LINE : " << *line3 << endl;
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
}

void rotate(Image &image) {
    Figure *f;
    float radius;
    int pointX1 = 0,
            pointY1 = 0;
    int choice_user = -1;

    if (image.getCount() == 0) {
        cout << "Draw something before perform any operation." << endl;
        return;
    }
    showImageWithIndex(image);
    do {
        cout << "On which figure you want to perform operations :";
        cin >> choice_user;
    } while (!isValidChoice(choice_user, 1, image.getCount(), "Please, choose a correct choice."));
    do {
        cout << "How many degrees : ";
        cin >> radius;
    } while (!isValidChoice(radius, -360, 360,
                            "Please enter a valid degree rotation (-360 < r < 360)"));
    cout << "Coordinate of the rotation point : " << endl;
    askCoordinate(pointX1, "X");
    askCoordinate(pointY1, "Y");
    f = image.get(choice_user - 1);
    image.add(*f->rotate(radius, pointX1, pointY1));
    image.remove(*f);
    cout << "Shape rotated.\n" << endl;
}

void translate(Image &image) {
    Figure *f;
    int pointX1 = 0,
            pointY1 = 0;
    int choice_user = -1;

    if (image.getCount() == 0) {
        cout << "Draw something before perform any operation." << endl;
        return;
    }
    showImageWithIndex(image);
    do {
        cout << "On which figure you want to perform operations :";
        cin >> choice_user;
    } while (!isValidChoice(choice_user, 1, image.getCount(), "Please, choose a correct choice."));

    cout << "Translation point :" << endl;
    askCoordinate(pointX1, "X");
    askCoordinate(pointY1, "Y");


    f = image.get(choice_user - 1);
    image.add(*f->translate(Point(pointX1, pointY1)));
    image.remove(*f);
    cout << "Shape scaled.\n" << endl;
}

int startCli() {
    std::ofstream ofile;
    std::ifstream ifile;

    Choice choiceAction;
    bool finish = false;
    struct sockaddr_in server_addr;
    int portNum = 1500;
    std::string ip = "127.0.0.1";

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    Client client = Client(server_addr);

    Image image, imageServer;

    cout << "******************************************" << endl;
    cout << "*                                        *" << endl;
    cout << "* Welcome to the Patchwork application ! *" << endl;
    cout << "*                                        *" << endl;
    cout << "******************************************" << endl << endl;

    while (!finish) {
        choiceAction = nextChoice(image);

        switch (choiceAction) {
            case DRAW_IMAGE:
                image.add(*createImage());
                cout << "Image drawn." << endl;
                break;
            case DRAW_LINE:
                image.add(*createLine());
                cout << "Line drawn." << endl;
                break;
            case DRAW_CIRCLE:
                image.add(*createCircle());
                cout << "Circle drawn." << endl;
                break;
            case DRAW_RECTANGLE:
                image.add(*createRectangle());
                cout << "Rectangle drawn." << endl;
                break;
            case DRAW_POLYGON:
                image.add(*createPolygon());
                cout << "Polygon drawn." << endl;
                break;
            default:
                showImageWithIndex(image);
                break;
            case EXIT:
                finish = true;
                clear_history();
                break;
            case ROTATE:
                rotate(image);
                break;
            case TRANSLATE:
                translate(image);
                break;
            case CLEAR:
                image = Image();
                break;
            case SEND:
                try {
                    client.start();
                    client.sendFigure(image);
                    image = Image();
                } catch (const std::exception &e) {
                    cerr << e.what() << endl;
                }
                try {
                    client.stop();
                } catch (const std::exception &e) {
                    // Nothing todo
                }
                break;
            case RECEIVE:
                try {
                    client.start();
                    image = client.getImage();
                } catch (const std::exception &e) {
                    cerr << e.what() << endl;
                }
                try {
                    client.stop();
                } catch (const std::exception &e) {
                    // Nothing todo
                }
                break;
            case EXPORT:
                ofile.open("export.txt");
                ofile << imageServer.encode();
                ofile.close();
                cout << "Exported to " << "export.txt" << endl;
                break;
            case IMPORT:
                ifile.open("import.txt");
                image.add(*Figure::decode(ifile));
                ifile.close();
                cout << "Imported from " << "import.txt" << endl;
                break;
        }
        cout << endl << "Press any key to continue ...";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }
    return 0;
}

void showImageWithIndex(Image image) {
    for (int i = 0; i < image.getCount(); i++) {
        cout << (i + 1) << ". " << *image.get(i) << endl;
    }
}

void askCoordinate(int &point, string whichCoord) {
    do {
        cout << "Coordinate for " << whichCoord << " : ";
        cin >> point;
    } while (!isValidChoice(point, 0, 100, "Please, enter a valid coordinate (-100 < X < 100)"));
}

template<typename Type>
bool isValidChoice(Type choice, int boundM, int boundP, string errorMessage) {
    if (!cin || choice < boundM || choice > boundP) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << errorMessage << endl;
        return false;
    }
    return true;
}


Image *createImage() {
    cout << "Drawing an Image" << endl;
    int pointX = 0, pointY = 0;

    askCoordinate(pointX, "X");
    askCoordinate(pointY, "Y");

    return new Image(*new Point(pointX, pointY));
}

Line *createLine() {
    cout << "Drawing a Line" << endl;

    int pointX1 = 0, pointY1 = 0, pointX2 = 0, pointY2 = 0;
    cout << "Point A" << endl;
    askCoordinate(pointX1, "X");
    askCoordinate(pointY1, "Y");

    cout << "Point B" << endl;
    askCoordinate(pointX2, "X");
    askCoordinate(pointY2, "Y");

    return new Line(*new Point(pointX1, pointY1), *new Point(pointX2, pointY2));
}

Circle *createCircle() {
    int pointX1 = 0, pointY1 = 0;
    float radius = 0;
    cout << "Drawing a Circle" << endl;
    cout << "Center of the circle" << endl;
    askCoordinate(pointX1, "X");
    askCoordinate(pointY1, "Y");

    do {
        cout << "Radius of the circle : ";
        cin >> radius;
    } while (!isValidChoice(radius, 0, 100, "Please, enter a valid radius (0 < r < 100)"));

    return new Circle(*new Point(pointX1, pointY1), radius);
}

Rectangle *createRectangle() {
    int pointX1 = 0, pointY1 = 0, pointX2 = 0, pointY2 = 0;
    cout << "Drawing a rectangle" << endl;

    cout << "Point of top-left corner" << endl;
    askCoordinate(pointX1, "X");
    askCoordinate(pointY1, "Y");

    cout << "Point of bottom-right corner" << endl;
    askCoordinate(pointX2, "X");
    askCoordinate(pointY2, "Y");

    return new Rectangle(*new Point(pointX1, pointY1), *new Point(pointX2, pointY2));
}

Polygon *createPolygon() {
    int choice_user = 0, pointX1 = 0, pointY1 = 0;
    Polygon *polygon = new Polygon();
    cout << "Drawing a polygon" << endl;

    do {
        cout << "How many points do you want : " << endl;
        cin >> choice_user;
    } while (!isValidChoice(choice_user, 1, 50, "Please, choose a correct choice. (0 < x < 50"));
    for (int i = 0; i < choice_user; i++) {
        cout << "Point " << i << " : " << endl;
        askCoordinate(pointX1, "X");
        askCoordinate(pointY1, "Y");
        polygon->addPoint(*new Point(pointX1, pointY1));
    }
    return polygon;
}