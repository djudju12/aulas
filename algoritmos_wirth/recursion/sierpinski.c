#include "raylib.h"
#include <assert.h>
#include <unistd.h>

double _x0, _y0, u;

enum {UP, DOWN, LEFT, RIGHT} Direction;

void A(int);
void B(int);
void C(int);
void D(int);
void line(int, double);

#define DRAW_CROSS 0

int main(void)
{
    const int w = 600;
    const int h = 600;
    double MAX_SIZE = 600 / 4;
    int i = 0;

    InitWindow(w, h, "sierpinski curves");
    while (!WindowShouldClose())
    {
        if (i == 0 || i > 5 ) {
            i = 1;
            u = MAX_SIZE;
            _x0 = w/2.0 + u/4.0; _y0 = h/2.0 + u/1.25;
        }

        _x0 -= u;
        u /= 2.0;
        _y0 += u;
        BeginDrawing();
        {
            // if (i == 1) ClearBackground(CLITERAL(Color){ 18, 18, 18, 255 });
            ClearBackground(CLITERAL(Color){ 18, 18, 18, 255 });
            if (DRAW_CROSS) {
                DrawLineEx((Vector2) {w/2.0, 0}, (Vector2) {w/2.0, h}, 2, RED);
                DrawLineEx((Vector2) {0, h/2.0}, (Vector2) {w, h/2.0}, 2, RED);
            }

            A(i); line(7, u);
            B(i); line(5, u);
            C(i); line(3, u);
            D(i); line(1, u);
        }
        EndDrawing();
        WaitTime(0.6);
        i++;
    }

    CloseWindow();
    return 0;
}

void A(int i) {
    if (i > 0) {
        A(i-1); line(7, u);
        B(i-1); line(0, 2*u);
        D(i-1); line(1, u);
        A(i-1);
    }
}

void B(int i) {
    if (i > 0) {
        B(i-1); line(5, u);
        C(i-1); line(6, 2*u);
        A(i-1); line(7, u);
        B(i-1);
    }
}

void C(int i) {
    if (i > 0) {
        C(i-1); line(3, u);
        D(i-1); line(4, 2*u);
        B(i-1); line(5, u);
        C(i-1);
    }
}

void D(int i) {
    if (i > 0) {
        D(i-1); line(1, u);
        A(i-1); line(2, 2*u);
        C(i-1); line(3, u);
        D(i-1);
    }
}

void line(int d, double size) {
    assert(d >= 0 && d < 8  && "`d` must be between 0 and 7");

    double angle = d * 45.0;
    double radian = angle * (PI / 180.0);
    double x1 = _x0 + cos(radian) * size;
    double y1 = _y0 + sin(radian) * size;
    DrawLineEx((Vector2) {_x0, _y0}, (Vector2) {x1, y1}, 2, LIME);
    _x0 = x1; _y0 = y1;
}

