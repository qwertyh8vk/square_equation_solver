// пока что здесь нихуя нет. добавлять что либо буду по необходимости.
#include "raylib.h" // todo

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

void draw_axes(int multiplier); /* рисует и разметку и декарта */
void draw_graph_by_dots(int multiplier,
                        double coef_a, double coef_b, double coef_c);
void draw_graph_by_spline(int multiplier);
