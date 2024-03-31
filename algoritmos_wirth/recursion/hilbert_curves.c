#include "raylib.h"
#include <assert.h>
#include <unistd.h>

double _x0, _y0, u;

enum {UP, DOWN, LEFT, RIGHT} Direction;

void A(int);
void B(int);
void C(int);
void D(int);
void line(int, int);

int main(void)
{
    const int w = 600;
    const int h = 600;
    _x0 = w;
    _y0 = 0;
    u = 60.0;
    int i = 1;

    InitWindow(w, h, "hilbert curves");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            u /= i;
            A(i++);
            _x0 = w; _y0 = h;
            u = 60.0;
            if (i > 6) i = 1;
            ClearBackground(CLITERAL(Color){ 18, 18, 18, 255 });
        }
        EndDrawing();
        WaitTime(0.6);
    }

    CloseWindow();
    return 0;
}

void A(int i) {
    if (i > 0) {
        D(i-1); line(4, u);
        A(i-1); line(6, u);
        A(i-1); line(0, u);
        B(i-1);
    }
}

void B(int i) {
    if (i > 0) {
        C(i-1); line(2, u);
        B(i-1); line(0, u);
        B(i-1); line(6, u);
        A(i-1);
    }
}

void C(int i) {
    if (i > 0) {
        B(i-1); line(0, u);
        C(i-1); line(2, u);
        C(i-1); line(4, u);
        D(i-1);
    }
}

void D(int i) {
    if (i > 0) {
        A(i-1); line(6, u);
        D(i-1); line(4, u);
        D(i-1); line(2, u);
        C(i-1);
    }
}

void line(int d, int size) {
    assert(d >= 0 && d < 8  && "`d` must be between 0 and 7");

    double angle = d * 45.0;
    double radian = angle * (PI / 180.0);
    double x1 = _x0 + cos(radian) * size;
    double y1 = _y0 + sin(radian) * size;
    DrawLineEx((Vector2) {_x0, _y0}, (Vector2) {x1, y1}, 2, LIME);
    _x0 = x1; _y0 = y1;
}

