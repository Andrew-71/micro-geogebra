#ifndef MICRO_GEOGEBRA_VECTOR_OBJECT_H
#define MICRO_GEOGEBRA_VECTOR_OBJECT_H

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "point_object.h"

class Vector : public Point {
public:
    Vector(Point p1, Point p2) : Point(p2.x - p1.x, p2.y - p1.y) {}

    Vector(double x1, double y1, double x2, double y2) : Point(x1 - x2, y1 - y2) {}

    Vector(double x, double y) : Point(x, y) {}

    Vector(Point p) : Point(p) {}

    Vector(Vector const &v) = default;

    double dot_product(const Vector &other) {
        return (x * other.x) + (y * other.y);
    }

    Vector mul(double n) {
        return {x * n, y * n};
    }

    double cross_product(const Vector &other) {
        return x * other.y - y * other.x;
    }

    void reduce() {
        double divisor = gcd(std::abs(x), std::abs(y));
        x /= divisor;
        y /= divisor;
    }

    double get_angle(Vector v)
    {
        double angle = acos(((x * v.x) + (y * v.y)) / (abs() * v.abs()));
        if (std::isnan(angle))
        {
            return M_PI;
        }
        else return angle;
    }
};

// Function form of a method, included for backwards compatibility.
double get_angle(Vector v1, const Vector& v2)
{
    return v1.get_angle(v2);
}

#endif //MICRO_GEOGEBRA_VECTOR_OBJECT_H
