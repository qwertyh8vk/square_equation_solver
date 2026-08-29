#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "graphics.h"
#include "/opt/homebrew/Cellar/raylib/6.0/include/raylib.h" // todo

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

void draw_axes(int multiplier) {
    Vector2 x_axis_start = {0, SCREEN_HEIGHT / 2};
    Vector2 x_axis_end   = {SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    
    Vector2 y_axis_start = {SCREEN_WIDTH / 2, SCREEN_HEIGHT};
    Vector2 y_axis_end   = {SCREEN_WIDTH / 2, 0};

    DrawLineEx(x_axis_start, x_axis_end, 2, GRAY);
    DrawLineEx(y_axis_start, y_axis_end, 2, GRAY);

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

void draw_graph_by_dots(int multiplier) {
    for (double i = -40; i < 40; i += 0.05) {
        DrawCircle((i*multiplier) + SCREEN_WIDTH / 2, -(i*i*multiplier + 2*i - 10) + SCREEN_HEIGHT / 2, 2, DARKBLUE);
    }
}
void draw_graph_by_spline(int multiplier) {

}

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trial window");

    int multiplier = 40;
    int dmult = 10;

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();

            if (GetMouseWheelMove() > 0) {
                if (multiplier <= 600) {
                    multiplier += dmult;
                }
            }

            else if (GetMouseWheelMove() < 0) {
                if (multiplier >= 20) {
                    multiplier -= dmult;
                }
            }

            ClearBackground(BLACK);
            draw_axes(multiplier);
            draw_graph_by_dots(multiplier);

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}




void initialize_two_dimens_array() {
    char matrix[SIZE][SIZE];

    for(int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = ' ';
        }
    }

    for (int i = 0; i < SIZE; i++) {
        matrix[30][i] = '-';
        matrix[i][30] = '|';
    }

    matrix[30][30] = '0';
    matrix[30][32] = '2';
    matrix[28][30] = '2';

    matrix[29][31] = '*';
    matrix[26][32] = '*';
    matrix[21][33] = '*';
    matrix[14][34] = '*';
    matrix[5][35]  = '*';

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        
        printf("\n");
    }

}

// (1;1) (2;4) (3;9) (4;16) (5;25)