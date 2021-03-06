#ifndef MICRO_GEOGEBRA_LINE_OBJECT_H
#define MICRO_GEOGEBRA_LINE_OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "point_object.h"
#include "vector_object.h"

class Line: public BaseObject
{
public:
    double a, b, c;
    Point p1;
    Point p2;

    // This constructor will never be used
    Line(double A, double B, double C):p1(0, 0),p2(0, 0),BaseObject()
    {
        a = A;
        b = B;
        c = C;
    }
    Line(const Point& point1, const Point& point2):p1(point1),p2(point2),BaseObject()
    {
        p1.selected = false;
        p2.selected = false;
        a = point2.y - point1.y;
        b = point1.x - point2.x;
        c = (point1.y - point2.y) * point1.x + (point2.x - point1.x) * point1.y;
    }
    Line():p1(0, 0),p2(0,0),BaseObject(),a(0),b(0),c(0){}

    bool contains(const Point& p) const
    {
        if (a * p.x + b * p.y + c == 0) return true;
        return false;
    }

    bool same_side(const Point& point1, const Point& point2) const
    {
        if ((a * point1.x + b * point1.y + c > 0) == ((a * point2.x + b * point2.y + c > 0))) return true;
        return false;
    }

    double dist(const Point& p) const
    {
        return std::abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }

    Point cross(const Line& l) const
    {
        double x_cross = (l.b  * c - b * l.c) / (a * l.b - l.a * b);
        double y_cross = (a * l.c - l.a * c) / (a * l.b - l.a * b);
        return {x_cross * -1, y_cross * -1};
    }

    bool is_p(const Line& l) const
    {
        if ((Vector(a, b).cross_product(Vector(l.a, l.b))) == 0) return true;
        return false;
    }

    bool is_perpendicular(const Line& l) const
    {
        if ((Vector(a, b).dot_product(Vector(l.a, l.b)) == 0)) return true;
        return false;
    }

    Line parallel(double d) const
    {
        double increase = -((a * a * d) / sqrt(a * a + b * b)) - ((b * b * d) / sqrt(a * a + b * b));
        return {a, b, c + increase};
    }

    Point foot_of_perp(const Point& p) const
    {
        Vector v(b, a);
        Line l(v.x, -1 *v.y, ((-1 * v.x * p.x) + (v.y * p.y)));
        return cross(l);
    }

    Line perpendicular(const Point& p) const
    {
        Vector v(b, a);
        return {v.x, -1 *v.y, ((-1 * v.x * p.x) + (v.y * p.y))};
    }

    bool is_touched()
    {
        return (p1.is_touched() || p2.is_touched());
    }

    void change_select()
    {
        selected = !selected;
        p1.selected = selected;
        p2.selected = selected;
    }

    void change_colour(Color new_colour)
    {
        p1.colour = new_colour;
        p2.colour = new_colour;
    }

    void draw()
    {
        if (selected) DrawLine(p1.x, p1.y, p2.x, p2.y, GREEN);
        else DrawLine(p1.x, p1.y, p2.x, p2.y, BLACK);
        p1.draw();
        p2.draw();
    }
};

// Function form of Line's method, added for backwards compatibility with old code.
Line perpendicular(const Line& l, const Point& p)
{
    return l.perpendicular(p);
}

#endif //MICRO_GEOGEBRA_LINE_OBJECT_H
