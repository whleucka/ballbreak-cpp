#include "ball.h"
#include "globals.h"

Ball::Ball(int cx, int cy, int cr) {
    x = cx;
    y = cy;
    r = cr;
}

Ball::~Ball() {
}

void Ball::draw() {
    al_draw_filled_circle(x, y, r, al_map_rgba(255, 255, 255, 255));
}

void Ball::move() {
    direction();
    x = x + speed * dx;
    y = y + speed * dy;
}

void Ball::direction() {
    if (x + speed >= SCREEN_WIDTH) {
        dx = -1;
    } else if (x - speed <= 0) {
        dx = 1;
    }
    if (y + speed >= SCREEN_HEIGHT) {
        dy = -1;
    } else if (y - speed <= 0) {
        dy = 1;
    }
}
