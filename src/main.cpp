#include "raylib.h"

#include <cmath>
#include <vector>
#include <map>

#include "point_object.h"
#include "vector_object.h"
#include "line_object.h"
#include "circle_object.h"
#include "triangle_object.h"

#include "base_object.h"

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
    // Vector for buttons
    std::vector<BaseButton*> buttons(0);

    buttons.push_back(new EraseButton(640, 10, 135, 40));

    buttons.push_back(new ColourButton(640, 140, 60, 40, BLUE, SKYBLUE));
    buttons.push_back(new ColourButton(640, 140, 60, 40, BLUE, SKYBLUE));
    buttons.push_back(new ColourButton((640 + 67 + 8), 90, 60, 40, LIME, GREEN));
    buttons.push_back(new ColourButton((640 + 67 + 8), 140, 60, 40, GOLD, YELLOW));
    buttons.push_back(new ColourButton(640, 90, 60, 40, MAROON, RED));

    buttons.push_back(new ActionButton(640, 330, 135, 40, "Create line"));
    buttons.push_back(new ActionButton(640, 380, 135, 40, "Create triangle"));
    buttons.push_back(new ActionButton(640, 280, 60, 40, "Inner\nCircle"));
    buttons.push_back(new ActionButton((640 + 67 + 8), 280, 60, 40, "Outer\nCircle"));
    buttons.push_back(new ActionButton((640 + 67 + 8), 230, 60, 40, "Perp.\nLine"));
    buttons.push_back(new ActionButton(640, 230, 60, 40, "Line\nCross."));

    // Vector for objects
    std::vector<BaseObject*> object_vector(0);

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
            // Check buttons ======================================================================
            for (auto btn = std::begin(buttons); btn != std::end(buttons); ++btn)
            {
                if ((*btn)->is_hovered())
                {
                    if (dynamic_cast<EraseButton*>((*btn)) != NULL) object_vector.clear();  // Clear button

                    // Colour buttons
                    if (dynamic_cast<ColourButton*>((*btn)) != NULL)
                    {
                        for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                        {
                            if ((*i)->selected)
                            {
                                (*i)->change_colour((*btn)->colour);
                                (*i)->change_select();
                            }
                        }
                    }

                    // Action buttons
                    if (dynamic_cast<ActionButton*>((*btn)) != NULL)
                    {
                        auto *action_btn(dynamic_cast<ActionButton*>((*btn)));
                        if (action_btn->label == "Create line" && CAN_CREATE_LINE)
                        {
                            Point *p1, *p2;
                            int index = 0;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Point*>((*i)) != NULL)
                                {
                                    p1 = dynamic_cast<Point*>((*i));
                                    object_vector.erase(object_vector.begin() + index);
                                    break;
                                }
                                index++;
                            }
                            index = 0;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Point*>((*i)) != NULL)
                                {
                                    p2 = dynamic_cast<Point*>((*i));
                                    object_vector.erase(object_vector.begin() + index);
                                    break;
                                }
                                index++;
                            }
                            object_vector.push_back(new Line(*p1, *p2));
                        }
                        if (action_btn->label == "Create triangle" && CAN_CREATE_TRIANGLE)
                        {
                            Point *p1, *p2, *p3;
                            int index = 0;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Point*>((*i)) != NULL)
                                {
                                    p1 = dynamic_cast<Point*>((*i));
                                    object_vector.erase(object_vector.begin() + index);
                                    break;
                                }
                                index++;
                            }
                            index = 0;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Point*>((*i)) != NULL)
                                {
                                    p2 = dynamic_cast<Point*>((*i));
                                    object_vector.erase(object_vector.begin() + index);
                                    break;
                                }
                                index++;
                            }
                            index = 0;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Point*>((*i)) != NULL)
                                {
                                    p3 = dynamic_cast<Point*>((*i));
                                    object_vector.erase(object_vector.begin() + index);
                                    break;
                                }
                                index++;
                            }
                            object_vector.push_back(new Triangle(*p1, *p2, *p3));
                        }
                        if (action_btn->label == "Inner\nCircle" && CAN_CREATE_INNER_CIRCLE)
                        {
                            Triangle *t;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected && dynamic_cast<Triangle*>((*i)) != NULL)
                                {
                                    t = dynamic_cast<Triangle*>((*i));
                                    object_vector.push_back(new Circle((*t).bisector_interception(),
                                                                   Line((*t).a, (*t).b).dist((*t).bisector_interception())));
                                    (*i)->change_select();
                                    break;
                                }
                            }
                        }
                        if (action_btn->label == "Outer\nCircle" && CAN_CREATE_OUTER_CIRCLE)
                        {
                            Triangle *t;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected && dynamic_cast<Triangle*>((*i)) != NULL)
                                {
                                    t = dynamic_cast<Triangle*>((*i));
                                    Point p_cross((*t).outer_circle_centre());
                                    object_vector.push_back(new Circle(p_cross, p_cross.dist((*t).a)));
                                    (*i)->change_select();
                                    break;
                                }
                            }
                        }
                        if (action_btn->label == "Perp.\nLine" && CAN_CREATE_PERPENDICULAR_LINE)
                        {
                            Point *p;
                            Line *l;
                            int index = 0;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Point*>((*i)) != NULL)
                                {
                                    p = dynamic_cast<Point*>((*i));
                                    object_vector.erase(object_vector.begin() + index);
                                    break;
                                }
                                index++;
                            }
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Line*>((*i)) != NULL)
                                {
                                    l = dynamic_cast<Line*>((*i));
                                    (*i)->change_select();
                                    break;
                                }
                            }
                            object_vector.push_back(new Line(*p, (*l).foot_of_perp(*p)));
                        }
                        if (action_btn->label == "Line\nCross." && CAN_CREATE_LINE_CROSSING)
                        {
                            Line *l1, *l2;
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Line*>((*i)) != NULL)
                                {
                                    l1 = dynamic_cast<Line*>((*i));
                                    (*i)->change_select();
                                    break;
                                }
                            }
                            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
                            {
                                if ((*i)->selected and dynamic_cast<Line*>((*i)) != NULL)
                                {
                                    l2 = dynamic_cast<Line*>((*i));
                                    (*i)->change_select();
                                    break;
                                }
                            }
                            object_vector.push_back(new Point((*l1).cross(*l2)));
                        }
                    }
                }
            }
            // ====================================================================================


            // Process selection & deletion =======================================================
            bool did_action = false;
            int index = 0;
            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
            {
                if ((*i)->is_touched())
                {
                    did_action = true;
                    if (DELETE_STATE)
                    {
                        object_vector.erase(object_vector.begin() + index);
                        break;
                    }
                    else
                    {
                        (*i)->change_select();
                    }
                }
                index++;
            }
            // ====================================================================================

            // Process amount of selected items of each type ======================================
            int amount_selected_points = 0;
            int amount_selected_lines = 0;
            int amount_selected_triangles = 0;
            int amount_selected_circles = 0;
            for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
            {
                if ((*i)->selected)
                {
                    if (dynamic_cast<Point*>((*i)) != NULL) amount_selected_points++;
                    if (dynamic_cast<Line*>((*i)) != NULL) amount_selected_lines++;
                    if (dynamic_cast<Triangle*>((*i)) != NULL) amount_selected_triangles++;
                    if (dynamic_cast<Circle*>((*i)) != NULL) amount_selected_circles++;
                }
            }
            // ====================================================================================

            // Reset system variables =============================================================
            CAN_CREATE_INNER_CIRCLE = CAN_CREATE_OUTER_CIRCLE = (amount_selected_triangles == 1);

            CAN_CREATE_LINE = (amount_selected_points == 2);

            CAN_CREATE_TRIANGLE = (amount_selected_points == 3);

            CAN_CREATE_LINE_CROSSING = (amount_selected_lines == 2);

            CAN_CREATE_PERPENDICULAR_LINE = (amount_selected_lines == 1 && amount_selected_points == 1);
            // ====================================================================================


            // Create a point if we didn't touch anything =========================================
            if (not did_action and not DELETE_STATE and GetMouseX() < 600)
            {
                object_vector.push_back(new Point(GetMouseX(), GetMouseY()));
            }
            // ====================================================================================
        }

        BeginDrawing();

        // Draw objects
        for (auto i = std::begin(object_vector); i != std::end(object_vector); ++i)
        {
            (*i)->draw();
        }

        DrawUi(DELETE_STATE); // Draw UI

        // Draw buttons
        std::map<std::string, bool> conditions = {
                { "Create line", CAN_CREATE_LINE},
                {"Create triangle", CAN_CREATE_TRIANGLE},
                {"Inner\nCircle", CAN_CREATE_INNER_CIRCLE},
                {"Outer\nCircle", CAN_CREATE_OUTER_CIRCLE},
                {"Perp.\nLine", CAN_CREATE_PERPENDICULAR_LINE},
                {"Line\nCross.", CAN_CREATE_LINE_CROSSING}
        };
        for (auto i = std::begin(buttons); i != std::end(buttons); ++i)
        {
            if (dynamic_cast<ActionButton*>(*i) != NULL)
            {
                (*dynamic_cast<ActionButton*>(*i)).draw(conditions.find((dynamic_cast<ActionButton*>(*i)->label))->second);
            }
            else
            {
                (*i)->draw();
            }
        }

        // Clear background
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}