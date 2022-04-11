#ifndef MICRO_GEOGEBRA_POINT_OBJECT_H
#define MICRO_GEOGEBRA_POINT_OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cmath>
#include "base_object.h"

// Function for recursively finding the greatest common divisors of 2 numbers
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

class Point: public BaseObject
{
public:
    // Polar coordinates feature has been retired due to its inability to work with new code
    Point(double x_in, double y_in, Color point_colour=BLACK, bool select=false): BaseObject(x_in, y_in, point_colour, select){}
    Point(Point const &p): BaseObject(p){}
    Point():BaseObject(){}

    int id;

    double dist(Point const &p=Point(0, 0))
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }

    double dist(double x_in, double y_in)
    {
        return sqrt((x - x_in) * (x - x_in) + (y - y_in) * (y - y_in));
    }

    double abs()
    {
        return dist();
    }

    void draw()
    {
        if (not selected) DrawCircle(x, y, 5, colour);
        else DrawCircleGradient(x, y, 5, colour, GREEN);
    }
};

#endif //MICRO_GEOGEBRA_POINT_OBJECT_H
