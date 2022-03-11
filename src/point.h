#ifndef POINT_H
#define POINT_H

#include "raylib.h"
#include <iostream>
#include <cmath>

// Function for recursively finding the greatest common divisors of 2 numbers
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

class Point
{
public:

    double x, y;
    bool selected;
    Color colour;

    Point(double x_in, double y_in, bool polar=false, Color point_colour=BLACK)
    {
        if (not polar)
        {
            x = x_in;
            y = y_in;
        }
        else
        {
            x = x_in * cos(y_in);
            y = x_in * sin(y_in);
        }
        selected = false;
        colour = point_colour;
    }
    Point(Point const &p)
    {
        x = p.x;
        y = p.y;
        selected = p.selected;
        colour = p.colour;
    }
    Point():x(0),y(0),selected(false),colour(BLACK){}

    double abs()
    {
        return dist();
    }

    double dist(Point const &p=Point(0, 0))
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }

    double dist(double x_in, double y_in)
    {
        return sqrt((x - x_in) * (x - x_in) + (y - y_in) * (y - y_in));
    }

    void draw() const
    {
        if (not selected) DrawCircle(x, y, 5, colour);
        else DrawCircleGradient(x, y, 5, colour, GREEN);
    }
};

#endif //POINT_H

