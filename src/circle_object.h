#ifndef MICRO_GEOGEBRA_CIRCLE_OBJECT_H
#define MICRO_GEOGEBRA_CIRCLE_OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "point_object.h"
#include "vector_object.h"
#include "line_object.h"

class Circle: public BaseObject
{
public:
    double r;

    Circle(double x, double y, double radius) : BaseObject(x, y){
        r = radius;
    }
    Circle(const Point& p, double radius) : BaseObject(p){
        r = radius;
        selected = false;
    }
    Circle():r(0),BaseObject(){}

    double dist(const Line& l)
    {
        double dist_calculated = l.dist(Point(x, y)) - r;
        if (dist_calculated < 0) return 0;
        else return dist_calculated;
    }

    bool touches(const Line& l)
    {
        double dist_calculated = l.dist(Point(x, y)) - r;
        if (dist_calculated == 0) return true;
        return false;
    }

    void change_colour(Color new_colour)
    {
        colour = new_colour;
    }

    void change_select()
    {
        selected = !selected;
    }

    void draw()
    {
        if (selected) DrawCircleLines(x, y, r, GREEN);
        else DrawCircleLines(x, y, r, BLACK);
        Point(x, y, colour, selected).draw();
    }
};

#endif //MICRO_GEOGEBRA_CIRCLE_OBJECT_H
