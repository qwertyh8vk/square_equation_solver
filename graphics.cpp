#include "graphics.h"
#include "square_solver.h"

void draw_axes(int multiplier) {
    Vector2 x_axis_start = {0, SCREEN_HEIGHT / 2};
    Vector2 x_axis_end   = {SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    
    Vector2 y_axis_start = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
    Vector2 y_axis_end   = {SCREEN_WIDTH / 2, 0};

    DrawLineEx(x_axis_start, x_axis_end, 2, DARKBLUE);
    DrawLineEx(y_axis_start, y_axis_end, 2, DARKBLUE);

    //разметка вдоль y
    for (int x = SCREEN_WIDTH / 2; x > 0; x -= multiplier) {
        DrawLine(x, 0, x, SCREEN_HEIGHT, DARKGRAY);
    }

    for (int x = SCREEN_WIDTH / 2; x < SCREEN_WIDTH; x += multiplier) {
        DrawLine(x, 0, x, SCREEN_HEIGHT, DARKGRAY);
    }

    //разметка вдоль x
    for (int y = SCREEN_HEIGHT / 2; y > 0; y -= multiplier) {
        DrawLine(0, y, SCREEN_WIDTH, y, DARKGRAY);
    }

    for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y += multiplier) {
        DrawLine(0, y, SCREEN_WIDTH, y, DARKGRAY);
    }
}

void draw_graph_by_dots(int multiplier,
                        double coef_a, double coef_b, double coef_c) 
{
    for (double i = X_MIN; i < X_MAX; i += 2 * dX) {
        DrawCircle((i*multiplier) + SCREEN_WIDTH / 2, -((coef_a*i*i + coef_b*i + coef_c)*multiplier) + SCREEN_HEIGHT / 2, 2.75, MAGENTA);
    }
}

void draw_graph_by_spline(int multiplier,
                          double coef_a, double coef_b, double coef_c) 
{
    Vector2 points[MAX_NUM_OF_POINTS];
    int p = 0;
    for (double i = X_MIN; i < X_MAX; i += dX) {

        points[p].x = ((i)*multiplier + SCREEN_WIDTH  / 2);
        points[p].y = ((-1)*(coef_a*i*i + coef_b*i + coef_c)*multiplier + SCREEN_HEIGHT / 2);
        p += 1;

    }
    DrawSplineCatmullRom(points, MAX_NUM_OF_POINTS, 2, MAGENTA);
}

