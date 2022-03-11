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

#endif //BUTTON_H
