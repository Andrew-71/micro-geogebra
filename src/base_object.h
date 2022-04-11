#ifndef MICRO_GEOGEBRA_BASE_OBJECT_H
#define MICRO_GEOGEBRA_BASE_OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cmath>

class BaseObject
{
public:
    double x, y;
    bool selected;
    Color colour;

    BaseObject(double x1, double y1, Color given_colour=BLACK, bool select=false)
    {
        x = x1;
        y = y1;
        colour = given_colour;
        selected = select;
    }
    BaseObject(BaseObject const &other)
    {
        x = other.x;
        y = other.y;
        selected = other.selected;
        colour = other.colour;
    }
    BaseObject():x(0),y(0),selected(false),colour(BLACK){}


    virtual bool is_touched()
    {
        return (sqrt((x - GetMouseX()) * (x - GetMouseX()) + (y - GetMouseY()) * (y - GetMouseY())) < 4);
    }

    virtual void change_colour(Color new_colour)
    {
        colour = new_colour;
    }
    virtual void change_select()
    {
        selected = !selected;
    }
    virtual void draw()
    {
        DrawPixel(x, y, colour);
    }
};

#endif //MICRO_GEOGEBRA_BASE_OBJECT_H
