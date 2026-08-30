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
                        double coef_a, double coef_b, double coef_c) {
    for (double i = -40; i < 40; i += 0.05) {
        DrawCircle((i*multiplier) + SCREEN_WIDTH / 2, -((coef_a*i*i + coef_b*i + coef_c)*multiplier) + SCREEN_HEIGHT / 2, 1.75, VIOLET);
    }
}

void draw_graph_by_spline(int multiplier) {

}
// int main() {

//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trial window");

//     int multiplier = 40;
//     int dmult = 10;

//     SetTargetFPS(60);

//     while (!WindowShouldClose()) 
//     {
//         BeginDrawing();

//             if (GetMouseWheelMove() > 0) {
//                 if (multiplier <= 600) {
//                     multiplier += dmult;
//                 }
//             }

//             else if (GetMouseWheelMove() < 0) {
//                 if (multiplier >= 20) {
//                     multiplier -= dmult;
//                 }
//             }

//             ClearBackground(BLACK);
//             draw_axes(multiplier);
//             draw_graph_by_dots(multiplier);

//         EndDrawing();
//     }
    
//     CloseWindow();
//     return 0;
// }
