#include "raylib.h"
#include <assert.h>
#include <unistd.h>

int _x0, _y0, u;

enum {UP, DOWN, LEFT, RIGHT} Direction;

void A(int);
void B(int);
void C(int);
void D(int);
void line(int);

int main(void)
{
    const int w = 600;
    const int h = 600;
    _x0 = w;
    _y0 = 0;
    u = 60;
    int i = 1;

    InitWindow(w, h, "hilbert curves");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            // DrawLineEx((Vector2) {0, h/2}, (Vector2) {w, h/2}, 2, RED);
            // DrawLineEx((Vector2) {w/2, 0}, (Vector2) {w/2, h}, 2, RED);
            u /= i;
            A(i);
            ClearBackground(CLITERAL(Color){ 18, 18, 18, 255 });
            u = 60;
            i++;
            _x0 = w;
            _y0 = 0;
            if (i > 6) i = 1;
            WaitTime(0.6);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void A(int i) {
    if (i > 0) {
        D(i-1); line(LEFT);
        A(i-1); line(DOWN);
        A(i-1); line(RIGHT);
        B(i-1);
    }
}

void B(int i) {
    if (i > 0) {
        C(i-1); line(UP);
        B(i-1); line(RIGHT);
        B(i-1); line(DOWN);
        A(i-1);
    }
}

void C(int i) {
    if (i > 0) {
        B(i-1); line(RIGHT);
        C(i-1); line(UP);
        C(i-1); line(LEFT);
        D(i-1);
    }
}

void D(int i) {
    if (i > 0) {
        A(i-1); line(DOWN);
        D(i-1); line(LEFT);
        D(i-1); line(UP);
        C(i-1);
    }
}

void line(int d) {
    int x1, y1;

    switch (d) {
        case UP: {
            x1 = _x0; y1 = _y0 - u;
        } break;

        case DOWN: {
            x1 = _x0; y1 = _y0 + u;
        } break;

        case LEFT: {
            x1 = _x0 - u; y1 = _y0;
        } break;

        case RIGHT: {
            x1 = _x0 + u; y1 = _y0;
        } break;

        default: {
            assert(0 && "unreachable");
        } break;
    }

    DrawLineEx((Vector2) {_x0, _y0}, (Vector2) {x1, y1}, 2, LIME);
    _x0 = x1; _y0 = y1;
}

