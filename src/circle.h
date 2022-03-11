#ifndef CIRCLE_H
#define CIRCLE_H

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "point.h"
#include "vector.h"
#include "line.h"

class Circle
{
public:
    Point centre;
    bool selected;
    double r;

    Circle(double x, double y, double radius) : centre(x, y) {
        r = radius;
        selected = false;
    }
    Circle(const Point& p, double radius) : centre(p) {
        r = radius;
        centre.selected = false;
        selected = false;
    }
    Circle():centre(),r(0),selected(false){}

    double dist(const Line& l)
    {
        double dist_calculated = l.dist(centre) - r;
        if (dist_calculated < 0) return 0;
        else return dist_calculated;
    }

    bool touches(const Line& l)
    {
        double dist_calculated = l.dist(centre) - r;
        if (dist_calculated == 0) return true;
        return false;
    }

    void change_select()
    {
        selected = !selected;
        centre.selected = selected;
    }

    void draw()
    {
        if (selected) DrawCircleLines(centre.x, centre.y, r, GREEN);
        else DrawCircleLines(centre.x, centre.y, r, BLACK);
        centre.draw();
    }
};

#endif //CIRCLE_H
