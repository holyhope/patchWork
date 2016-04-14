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

using namespace std;

void askCoordinate(int &pointX1, string whichCoord);

void showImageWithIndex(Image image);

template<typename Type>
bool isValidChoice(Type choice, int boundM, int boundP, string errorMessage);

void test1() {
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

    Line line(Point(1, 4), Point(6, 1));
    cout << "LINE : " << line << endl;
    cout << "Width : " << line.getWidth() << " Height " << line.getHeight() << endl;
    cout << "Area: " << line.area() << " Perimeter: " << line.perimeter() << endl;
    Line *line2 = (Line *) line.scale(-3.);
    cout << "NEW SCALING LINE : " << *line2 << endl;
    cout << "Width : " << line2->getWidth() << " Height " << line2->getHeight() << endl;
    cout << "Area: " << line2->area() << " Perimeter: " << line2->perimeter() << endl;

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

int startCli() {
    std::ofstream ofile;
    std::ifstream ifile;

    int choice_user = -1;
    int maxChoice = 0;
    bool finish = false;
    struct sockaddr_in server_addr;
    int portNum = 1500;
    char *input;
    std::string ip = "127.0.0.1";

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    Client client = Client(server_addr);

    Image image, imageServer;

    int pointX1 = 0,
            pointX2 = 0,
            pointY1 = 0,
            pointY2 = 0;
    float radius;
    Polygon polygon;

    cout << "******************************************" << endl;
    cout << "*                                        *" << endl;
    cout << "* Welcome to the Patchwork application ! *" << endl;
    cout << "*                                        *" << endl;
    cout << "******************************************" << endl << endl;

    while (!finish) {
        do {
            cout << "What do you want to do ?" << endl;
            cout << endl << "   **** Draw ****" << endl;
            cout << to_string(++maxChoice) << ".  Draw an Image" << endl;
            cout << to_string(++maxChoice) << ".  Draw a Line" << endl;
            cout << to_string(++maxChoice) << ".  Draw a Circle" << endl;
            cout << to_string(++maxChoice) << ".  Draw a Rectangle" << endl;
            cout << to_string(++maxChoice) << ".  Draw a Polygon" << endl;
            cout << endl << "   **** Operation ****" << endl;
            cout << to_string(++maxChoice) << ".  Perform a rotation" << endl;
            cout << to_string(++maxChoice) << ".  Perform a scale" << endl;
            cout << to_string(++maxChoice) << ".  Perform an homothecy" << endl;
            cout << endl << "   **** Other ****" << endl;
            cout << to_string(++maxChoice) << ".  Clear local image" << endl;
            cout << to_string(++maxChoice) << ". Sync with server" << endl;
            cout << to_string(++maxChoice) << ". Export to export.txt" << endl;
            cout << to_string(++maxChoice) << ". Import from import.txt" << endl;
            cout << "0.  Exit this awesome application" << endl;
            cout << endl;

            do {
                input = readline("Your choice : ");
                try {
                    choice_user = std::atoi(input);
                } catch (const std::invalid_argument &e) {
                    // Nothing to do
                }
            } while (0 > choice_user);
            add_history(input);

        } while (!isValidChoice(choice_user, 0, maxChoice + 1, "Please, choose a correct choice."));
        maxChoice = 0;

        cout << endl;

        switch (choice_user) {
            case 1:
                cout << "Drawing an Image" << endl;

                askCoordinate(pointX1, "X");
                askCoordinate(pointY1, "Y");

                image.add(Image(Point(pointX1, pointY1)));

                cout << "Image drawn." << endl;
                break;
            case 2:
                cout << "Drawing a Line" << endl;

                cout << "Point A" << endl;
                askCoordinate(pointX1, "X");
                askCoordinate(pointY1, "Y");

                cout << "Point B" << endl;
                askCoordinate(pointX2, "X");
                askCoordinate(pointY2, "Y");

                image.add(Line(Point(pointX1, pointY1), Point(pointX2, pointY2)));

                cout << "Line drawn." << endl;
                break;
            case 3:
                cout << "Drawing a Circle" << endl;

                cout << "Center of the circle" << endl;
                askCoordinate(pointX1, "X");
                askCoordinate(pointY1, "Y");

                do {
                    cout << "Radius of the circle";
                    cin >> radius;
                } while (!isValidChoice(radius, 0, 100, "Please, enter a valid radius (0 < r < 100)"));

                image.add(Circle(Point(pointX1, pointY1), radius));

                cout << "Circle drawn." << endl;
                break;
            case 4:
                cout << "Drawing a rectangle" << endl;

                cout << "Point of top-left corner" << endl;
                askCoordinate(pointX1, "X");
                askCoordinate(pointY1, "Y");

                cout << "Point of bottom-right corner" << endl;
                askCoordinate(pointX2, "X");
                askCoordinate(pointY2, "Y");

                image.add(Rectangle(Point(pointX1, pointY1), Point(pointX2, pointY2)));

                cout << "Rectangle drawn." << endl;
                break;
            case 5:
                cout << "Drawing a polygon" << endl;

                do {
                    cout << "How many points do you want : " << endl;
                    cin >> choice_user;
                } while (!isValidChoice(choice_user, 1, 50, "Please, choose a correct choice. (0 < x < 50"));
                for (int i = 0; i < choice_user; i++) {
                    cout << "Point " << i << " : " << endl;
                    askCoordinate(pointX1, "X");
                    askCoordinate(pointY1, "Y");
                    polygon.addPoint(*new Point(pointX1, pointY1));
                }
                cout << polygon << endl;
                image.add(polygon);
                break;
            case 6:
                if (image.getCount() == 0) {
                    cout << "Draw something before perform any operation." << endl;
                }
                else {
                    showImageWithIndex(image);
                    do {
                        cout << "On which image you want to perform operations :";
                        cin >> choice_user;
                    } while (!isValidChoice(choice_user, 1, image.getCount(), "Please, choose a correct choice."));
                    do {
                        cout << "How many degrees : ";
                        cin >> radius;
                    } while (!isValidChoice(radius, -360, 360,
                                            "Please enter a valid degree rotation (-360 < r < 360)"));
                    cout << "Coordinate of the rotation point : ";
                    askCoordinate(pointX1, "X");
                    askCoordinate(pointY1, "Y");
                    image.get(choice_user - 1)->rotate(radius, pointX1, pointY1);
                    cout << "Shape rotated.\n" << endl;
                }
                break;

            case 9:
                image = Image();
                break;
            case 10:
                try {
                    client.start();
                    client.sendFigure(image);
                    image = client.getImage();
                    client.stop();
                } catch (const std::exception &e) {
                    cerr << e.what() << endl;
                }
                break;
            case 11:
                ofile.open("export.txt");
                ofile << imageServer.encode();
                ofile.close();
                cout << "Exported to " << "export.txt" << endl;
                break;
            case 12:
                ifile.open("import.txt");
                image.add(*Figure::decode(ifile));
                ifile.close();
                cout << "Imported from " << "import.txt" << endl;
                break;
            case 0:
                finish = true;
                clear_history();
                break;
            default:
                cout << "An error occur, sorry !" << endl;
                return -1;
        }
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