#ifndef MICRO_GEOGEBRA_TRIANGLE_OBJECT_H
#define MICRO_GEOGEBRA_TRIANGLE_OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "point_object.h"
#include "vector_object.h"
#include "line_object.h"
#include "circle_object.h"


class Triangle: public BaseObject {
public:
    Point a;
    Point b;
    Point c;
    double ab, ac, bc;

    Triangle(const Point &a1, const Point &b1, const Point &c1) : a(a1), b(b1), c(c1), BaseObject() {
        // Calculate sides just so that we don't need to do that again.
        ab = sqrt(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y));
        ac = sqrt(abs(a.x - c.x) * abs(a.x - c.x) + abs(a.y - c.y) * abs(a.y - c.y));
        bc = sqrt(abs(b.x - c.x) * abs(b.x - c.x) + abs(b.y - c.y) * abs(b.y - c.y));

        // Set all selects' to false
        selected = false;
        a.selected = false;
        b.selected = false;
        c.selected = false;
    }

    Triangle() : a(), b(), c(), BaseObject(), ab(0), ac(0), bc(0) {};

    double area() {
        double semi_perimeter = (ab + ac + bc) / 2;
        return sqrt(semi_perimeter * (semi_perimeter - ab) * (semi_perimeter - ac) * (semi_perimeter - bc));
    }

    double get_triangle_angle(int index) {
        // Check for correct angle index
        if (index > 3 || index < 1) throw std::invalid_argument("Angle code must be 1, 2 or 3");

        // BAC
        if (index == 1) return Vector(a, b).get_angle(Vector(a, c));

            // ABC
        else if (index == 2) return Vector(b, a).get_angle(Vector(b, c));

            // ACB
        else return Vector(c, a).get_angle(Vector(c, b));
    }

    Line bisector(int index) {
        if (index > 3 || index < 1) throw std::invalid_argument("Angle code must be 1, 2 or 3");

        //        A
        //       /|\
        //      /"|"\
        //   a /  |  \ b
        //    /   |   \
        //   /    |    \
        //  /-----|-----\
        // C   n     m    B
        //
        //  a/b == n/m
        //
        // UPDATE AFTER 7-ISH ITERATIONS: IT WORKS, AND IT WAS EASIER THAN I THOUGHT

        // CAB
        if (index == 1) {
            Point n(c.x + (b.x - c.x) / (ab + ac) * ac,
                    c.y + (b.y - c.y) / (ab + ac) * ac);
            return {a, n};
        }

            // ACB
        else if (index == 2) {
            Point n(a.x + (b.x - a.x) / (bc + ac) * ac,
                    a.y + (b.y - a.y) / (bc + ac) * ac);
            return {c, n};
        }

            // ABC
        else {
            Point n(a.x + (c.x - a.x) / (bc + ab) * ab,
                    a.y + (c.y - a.y) / (bc + ab) * ab);
            return {b, n};
        }
    }

    Point median_interception() {
        Point a1((b.x + c.x) / 2, (b.y + c.y) / 2);
        return {((1 * a.x) + (2 * a1.x)) / 3, ((1 * a.y) + (2 * a1.y)) / 3};
    }

    Point bisector_interception() {
        return {bisector(1).cross(bisector(2))};
    }

    Point outer_circle_centre() {
        Point a_centre((a.x + b.x) / 2, (a.y + b.y) / 2);
        Point b_centre((a.x + c.x) / 2, (a.y + c.y) / 2);
        Line middle_a(perpendicular(Line(a, b), a_centre));
        Line middle_b(perpendicular(Line(a, c), b_centre));
        return middle_a.cross(middle_b);
    }

    double radius_of_inner_circle() {
        double semi_perimetre = (ab + ac + bc) / 2;
        double area = sqrt(semi_perimetre * (semi_perimetre - ab) * (semi_perimetre - ac) * (semi_perimetre - bc));

        return area / semi_perimetre;
    }

    double radius_of_outer_circle() {
        double semi_perimetre = (ab + ac + bc) / 2;
        double area = sqrt(semi_perimetre * (semi_perimetre - ab) * (semi_perimetre - ac) * (semi_perimetre - bc));

        return (ab * ac * bc) / (4 * area);
    }

    bool is_touched()
    {
        return (a.dist(Point(GetMouseX(), GetMouseY())) < 4 ||
            b.dist(Point(GetMouseX(), GetMouseY())) < 4 ||
            c.dist(Point(GetMouseX(), GetMouseY())) < 4);
    }

    void change_colour(Color new_colour)
    {
        colour = new_colour;
        a.colour = new_colour;
        b.colour = new_colour;
        c.colour = new_colour;
    }

    void change_select() {
        selected = !selected;
        a.selected = selected;
        b.selected = selected;
        c.selected = selected;
    }

    void draw() {
        if (selected) {
            DrawLine(a.x, a.y, b.x, b.y, GREEN);
            DrawLine(a.x, a.y, c.x, c.y, GREEN);
            DrawLine(b.x, b.y, c.x, c.y, GREEN);
            a.draw();
            b.draw();
            c.draw();
        } else {
            DrawLine(a.x, a.y, b.x, b.y, BLACK);
            DrawLine(a.x, a.y, c.x, c.y, BLACK);
            DrawLine(b.x, b.y, c.x, c.y, BLACK);
            a.draw();
            b.draw();
            c.draw();
        }
    }
};

#endif //MICRO_GEOGEBRA_TRIANGLE_OBJECT_H
