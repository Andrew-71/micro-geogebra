#include "raylib.h"

#include <iostream>
#include <cmath>
#include <vector>

#include "point.h"
#include "vector.h"
#include "line.h"
#include "circle.h"
#include "triangle.h"

#include "button.h"

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;


void DrawUi(bool DELETE_STATE)
{
    // UI Background
    DrawRectangle(600, 0, 500, 500, LIGHTGRAY);

    if (DELETE_STATE)
    {
        DrawText("Delete Mode", 10, 10, 15, RED);
    }
}


int main()
{
    // Button declarations
    //
    // Codes (not used):
    // 1 - Create Line
    // 2 - Create Triangle
    // 11 - Inner Circle
    // 12 - Outer Circle
    // 21 - Perpendicular Line
    // 22 - Line crossing
    //
    EraseButton clear_button(640, 10, 135, 40);
    Button create_line_btn(1, 640, 330, 135, 40, "Create line");
    Button create_triangle_btn(2, 640, 380, 135, 40, "Create triangle");
    Button inner_circle_btn(11, 640, 280, 60, 40, "Inner\nCircle");
    Button outer_circle_btn(12, (640 + 67 + 8), 280, 60, 40, "Outer\nCircle");
    Button perp_line_btn(21, (640 + 67 + 8), 230, 60, 40, "Perp.\nLine");
    Button line_cross_btn(22, 640, 230, 60, 40, "Line\nCross.");

    // Vectors for objects
    std::vector<Point> point_vector(0);
    std::vector<Triangle> triangle_vector(0);
    std::vector<Line> line_vector(0);
    std::vector<Circle> circle_vector(0);

    // System variables
    bool DELETE_STATE = false;
    bool CAN_CREATE_TRIANGLE = false;
    bool CAN_CREATE_LINE = false;
    bool CAN_CREATE_INNER_CIRCLE = false;
    bool CAN_CREATE_OUTER_CIRCLE = false;
    bool CAN_CREATE_LINE_CROSSING = false;
    bool CAN_CREATE_PERPENDICULAR_LINE = false;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GeomeTRY");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_D))
        {
            if (DELETE_STATE)
            {
                DELETE_STATE = false;
            }
            else DELETE_STATE = true;
        }

        // When mouse is clicked
        if (IsMouseButtonPressed(0))
        {
            // Check buttons ========================================
            if (clear_button.is_hovered())
            {
                point_vector.clear();
                triangle_vector.clear();
                line_vector.clear();
                circle_vector.clear();
            }
            if (create_line_btn.is_hovered() && CAN_CREATE_LINE)
            {
                Point p1, p2;
                int index = 0;
                for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
                {
                    if (i->selected)
                    {
                        p1 = Point(*i);
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    index++;
                }
                index = 0;
                for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
                {
                    if (i->selected)
                    {
                        p2 = Point(*i);
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    index++;
                }
                line_vector.push_back(Line(p1, p2));
            } // Line
            if (create_triangle_btn.is_hovered() && CAN_CREATE_TRIANGLE)
            {
                Point p1, p2, p3;
                int index = 0;
                for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
                {
                    if (i->selected)
                    {
                        p1 = Point(*i);
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    index++;
                }
                index = 0;
                for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
                {
                    if (i->selected)
                    {
                        p2 = Point(*i);
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    index++;
                }
                index = 0;
                for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
                {
                    if (i->selected)
                    {
                        p3 = Point(*i);
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    index++;
                }
                triangle_vector.push_back(Triangle(p1, p2, p3));
            } // Triangle
            if (outer_circle_btn.is_hovered() && CAN_CREATE_OUTER_CIRCLE)
            {
                for (auto i = std::begin(triangle_vector); i != std::end(triangle_vector); ++i)
                {
                    if (i->selected)
                    {
                        Point p_cross(i->outer_circle_centre());
                        circle_vector.push_back(Circle(p_cross, p_cross.dist(i->a)));
                        i->change_select();
                        break;
                    }
                }
            } // Outer circle
            if (inner_circle_btn.is_hovered() && CAN_CREATE_INNER_CIRCLE)
            {
                for (auto i = std::begin(triangle_vector); i != std::end(triangle_vector); ++i)
                {
                    if (i->selected)
                    {
                        circle_vector.push_back(Circle(i->bisector_interception(),
                                                       Line(i->a, i->b).dist(i->bisector_interception())));
                        i->change_select();
                        break;
                    }
                }
            } // Inner circle
            if (line_cross_btn.is_hovered() && CAN_CREATE_LINE_CROSSING)
            {
                Line l1, l2;
                for (auto i = std::begin(line_vector); i != std::end(line_vector); ++i)
                {
                    if (i->selected)
                    {
                        l1 = Line(*i);
                        i->change_select();
                        break;
                    }
                }
                for (auto i = std::begin(line_vector); i != std::end(line_vector); ++i)
                {
                    if (i->selected)
                    {
                        l2 = Line(*i);
                        i->change_select();
                        break;
                    }
                }
                point_vector.push_back(Point(l1.cross(l2)));
            } // Line cross
            if (perp_line_btn.is_hovered() && CAN_CREATE_PERPENDICULAR_LINE)
            {
                Line l;
                for (auto i = std::begin(line_vector); i != std::end(line_vector); ++i)
                {
                    if (i->selected)
                    {
                        l = Line(*i);
                        i->change_select();
                        break;
                    }
                }
                Point p;
                int index = 0;
                for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
                {
                    if (i->selected)
                    {
                        p = Point(*i);
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    index++;
                }
                line_vector.push_back(Line(p, l.foot_of_perp(p)));
            } // Perpendicular line

            // Process points =======================================
            bool did_action = false;
            int index = 0;
            int amount_selected_points = 0;
            for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i)
            {
                if (i->dist(Point(GetMouseX(), GetMouseY())) < 4)
                {
                    did_action = true;
                    if (DELETE_STATE)
                    {
                        point_vector.erase(point_vector.begin() + index);
                        break;
                    }
                    else
                    {
                        i->selected = !i->selected;
                    }
                }
                if (i->selected) amount_selected_points++;
                index++;
            }

            // Process lines ========================================
            index = 0;
            int amount_selected_lines = 0;
            for (auto i = std::begin(line_vector); i != std::end(line_vector); ++i)
            {
                if (i->p1.dist(Point(GetMouseX(), GetMouseY())) < 4 ||
                i->p2.dist(Point(GetMouseX(), GetMouseY())) < 4)
                {
                    did_action = true;
                    if (DELETE_STATE)
                    {
                        line_vector.erase(line_vector.begin() + index);
                        break;
                    }
                    else
                    {
                        i->change_select();
                    }
                }
                if (i->selected) amount_selected_lines++;
                index++;
            }

            // Process triangles ====================================
            index = 0;
            int amount_selected_triangles = 0;
            for (auto i = std::begin(triangle_vector); i != std::end(triangle_vector); ++i)
            {
                if (i->a.dist(Point(GetMouseX(), GetMouseY())) < 4 ||
                    i->b.dist(Point(GetMouseX(), GetMouseY())) < 4 ||
                    i->c.dist(Point(GetMouseX(), GetMouseY())) < 4)
                {
                    did_action = true;
                    if (DELETE_STATE)
                    {
                        triangle_vector.erase(triangle_vector.begin() + index);
                        break;
                    }
                    else
                    {
                        i->change_select();
                    }
                }
                if (i->selected) amount_selected_triangles++;
                index++;
            }

            // Process triangles ====================================
            index = 0;
            int amount_selected_circles = 0;
            for (auto i = std::begin(circle_vector); i != std::end(circle_vector); ++i)
            {
                if (i->centre.dist(Point(GetMouseX(), GetMouseY())) < 4)
                {
                    did_action = true;
                    if (DELETE_STATE)
                    {
                        circle_vector.erase(circle_vector.begin() + index);
                        break;
                    }
                    else
                    {
                        i->change_select();
                    }
                }
                if (i->selected) amount_selected_circles++;
                index++;
            }

            // Check system variables ===============================
            if (amount_selected_triangles == 1)
            {
                CAN_CREATE_INNER_CIRCLE = true;
                CAN_CREATE_OUTER_CIRCLE = true;
            }
            else
            {
                CAN_CREATE_INNER_CIRCLE = false;
                CAN_CREATE_OUTER_CIRCLE = false;
            }
            if (amount_selected_points == 2) CAN_CREATE_LINE = true;
            else CAN_CREATE_LINE = false;

            if (amount_selected_points == 3) CAN_CREATE_TRIANGLE = true;
            else CAN_CREATE_TRIANGLE = false;

            if (amount_selected_lines == 2) CAN_CREATE_LINE_CROSSING = true;
            else CAN_CREATE_LINE_CROSSING = false;

            if (amount_selected_lines == 1 && amount_selected_points == 1) CAN_CREATE_PERPENDICULAR_LINE = true;
            else CAN_CREATE_PERPENDICULAR_LINE = false;
            // ======================================================

            // Create a point =======================================
            if (not did_action and not DELETE_STATE and GetMouseX() < 600)
            {
                Point p(GetMouseX(), GetMouseY());
                point_vector.push_back(p);
            }
            // ======================================================
        }

        BeginDrawing();

        // Draw objects
        for (auto i = std::begin(point_vector); i != std::end(point_vector); ++i) i->draw();
        for (auto i = std::begin(triangle_vector); i != std::end(triangle_vector); ++i) i->draw();
        for (auto i = std::begin(line_vector); i != std::end(line_vector); ++i) i->draw();
        for (auto i = std::begin(circle_vector); i != std::end(circle_vector); ++i) i->draw();

        DrawUi(DELETE_STATE); // Draw UI

        // Draw buttons
        clear_button.draw();
        create_line_btn.draw(CAN_CREATE_LINE);
        create_triangle_btn.draw(CAN_CREATE_TRIANGLE);
        inner_circle_btn.draw(CAN_CREATE_INNER_CIRCLE);
        outer_circle_btn.draw(CAN_CREATE_OUTER_CIRCLE);
        perp_line_btn.draw(CAN_CREATE_PERPENDICULAR_LINE);
        line_cross_btn.draw(CAN_CREATE_LINE_CROSSING);

        // Clear background
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}