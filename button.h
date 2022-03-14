#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "raylib.h"

class Button
{
public:
    int code;
    int x, y, width, height;
    const char *label;

    Button(int return_code, int x_in, int y_in, int width_in, int height_in, const char* label_in)
    {
        code = return_code;
        x = x_in;
        y = y_in;
        width = width_in;
        height = height_in;
        label = label_in;
    }

    bool is_hovered(int x_mouse=GetMouseX(), int y_mouse=GetMouseY())
    {
        if ((x <= x_mouse && x + width >= x_mouse) && (y <= y_mouse && y + height >= y_mouse)) return true;
        return false;
    }

    void draw(bool condition)
    {
        int x_mouse = GetMouseX(), y_mouse = GetMouseY();
        if (condition)
        {
            if (is_hovered(x_mouse, y_mouse)) DrawRectangle(x, y, width, height, YELLOW);
            else DrawRectangle(x, y, width, height, GOLD);
        }
        else
        {
            if (is_hovered(x_mouse, y_mouse)) DrawRectangle(x, y, width, height, GRAY);
            else DrawRectangle(x, y, width, height, DARKGRAY);
        }
        DrawText(label, x + 10, y + 5, 12, BLACK);
    }
};

// A more watered-down version of Button for a specific purpose
class EraseButton
{
public:
    int x, y, width, height;

    EraseButton(int x_in, int y_in, int width_in, int height_in)
    {
        x = x_in;
        y = y_in;
        width = width_in;
        height = height_in;
    }

    bool is_hovered(int x_mouse=GetMouseX(), int y_mouse=GetMouseY())
    {
        if ((x <= x_mouse && x + width >= x_mouse) && (y <= y_mouse && y + height >= y_mouse)) return true;
        return false;
    }

    void draw()
    {
        if (is_hovered()) DrawRectangle(x, y, width, height, RED);
        else DrawRectangle(x, y, width, height, MAROON);

        DrawText("Clear", x + 10, y + 12, 15, BLACK);
    }
};

// Colour select button (circle)
class ColourButton
{
public:
    int x, y, r;
    Color colour;
    Color colour_hover;

    ColourButton(int x_in, int y_in, int radius, Color c, Color c_light)
    {
        x = x_in;
        y = y_in;
        r = radius;
        colour = c;
        colour_hover = c_light;
    }

    bool is_hovered(int x_mouse=GetMouseX(), int y_mouse=GetMouseY())
    {
        if (sqrt((y_mouse - y) * (y_mouse - y) + (x_mouse - x) * (x_mouse - x)) <= r) return true;
        return false;
    }

    void draw()
    {
        if (is_hovered()) DrawCircle(x, y, r, colour_hover);
        else DrawCircle(x, y, r, colour);
    }
};

// Colour select button (rectangle)
class ColourButtonRect
{
public:
    int x, y, width, height;
    Color colour;
    Color colour_hover;

    ColourButtonRect(int x_in, int y_in, int width_in, int height_in, Color c, Color c_light)
    {
        x = x_in;
        y = y_in;
        width = width_in;
        height = height_in;
        colour = c;
        colour_hover = c_light;
    }

    bool is_hovered(int x_mouse=GetMouseX(), int y_mouse=GetMouseY())
    {
        if ((x <= x_mouse && x + width >= x_mouse) && (y <= y_mouse && y + height >= y_mouse)) return true;
        return false;
    }

    void draw()
    {
        if (is_hovered()) DrawRectangle(x, y, width, height, colour_hover);
        else DrawRectangle(x, y, width, height, colour);
    }
};


std::vector<Point> change_colours(std::vector<Point> v, Color new_colour)
{
    for (auto i = std::begin(v); i != std::end(v); ++i)
    {
        if (i->selected)
        {
            i->colour = new_colour;
            i->selected = false;
        }
    }
    return v;
}

std::vector<Triangle> change_colours_triangles(std::vector<Triangle> v, Color new_colour)
{
    for (auto i = std::begin(v); i != std::end(v); ++i)
    {
        if (i->selected)
        {
            i->a.colour = new_colour;
            i->b.colour = new_colour;
            i->c.colour = new_colour;
            i->change_select();
        }
    }
    return v;
}

std::vector<Circle> change_colours_circles(std::vector<Circle> v, Color new_colour)
{
    for (auto i = std::begin(v); i != std::end(v); ++i)
    {
        if (i->selected)
        {
            i->centre.colour = new_colour;
            i->change_select();
        }
    }
    return v;
}

std::vector<Line> change_colours_line(std::vector<Line> v, Color new_colour)
{
    for (auto i = std::begin(v); i != std::end(v); ++i)
    {
        if (i->selected)
        {
            i->p1.colour = new_colour;
            i->p2.colour = new_colour;
            i->change_select();
        }
    }
    return v;
}


#endif //BUTTON_H
