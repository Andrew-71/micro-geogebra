#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "raylib.h"


class BaseButton
{
public:
    int x, y, width, height;
    Color colour;
    Color hover_colour;

    BaseButton():x(0),y(0), colour(BLACK), hover_colour(GRAY){}

    BaseButton(int x_in, int y_in, int width_in, int height_in, Color colour_given=DARKGRAY, Color hover_colour_given=GRAY)
    {
        x = x_in;
        y = y_in;
        width = width_in;
        height = height_in;
        colour = colour_given;
        hover_colour = hover_colour_given;
    }

    bool is_hovered(int x_mouse=GetMouseX(), int y_mouse=GetMouseY())
    {
        if ((x <= x_mouse && x + width >= x_mouse) && (y <= y_mouse && y + height >= y_mouse)) return true;
        return false;
    }


    virtual void draw()
    {
        if (is_hovered()) DrawRectangle(x, y, width, height, hover_colour);
        else DrawRectangle(x, y, width, height, colour);
    }
};

class ActionButton: public BaseButton
{
public:
    const char *label;

    ActionButton(int x_in, int y_in, int width_in, int height_in, const char* label_in): BaseButton(x_in, y_in, width_in, height_in)
    {
        label = label_in;
    }

    void draw(bool condition)
    {
        if (condition)
        {
            if (is_hovered()) DrawRectangle(x, y, width, height, YELLOW);
            else DrawRectangle(x, y, width, height, GOLD);
        }
        else
        {
            BaseButton::draw();
        }
        DrawText(label, x + 10, y + 5, 12, BLACK);
    }
};

class EraseButton: public BaseButton
{
public:
    EraseButton(int x_in, int y_in, int width_in, int height_in): BaseButton(x_in, y_in, width_in, height_in, MAROON, RED){}

    void draw()
    {
        if (is_hovered()) DrawRectangle(x, y, width, height, RED);
        else DrawRectangle(x, y, width, height, MAROON);

        DrawText("Clear", x + 10, y + 12, 15, BLACK);
    }
};

// Colour select button (circle)
class ColourButton:public BaseButton
{
public:
    ColourButton(int x_in, int y_in, int width_in, int height_in, Color c, Color c_light): BaseButton(x_in, y_in, width_in, height_in, c, c_light) {}
};


#endif //BUTTON_H
