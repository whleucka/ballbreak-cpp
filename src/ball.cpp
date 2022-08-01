#include "ball.h"
#include "globals.h"

Ball::Ball(int x, int y, int r) {
    this->x = x;
    this->y = y;
    this->r = r;
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

bool Ball::isMoving() {
    return dx != 0 && dy != 0;
}

void Ball::direction() {
    // Ball direction heading north, east, south, west
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

Point* Ball::getPosition() {
    Point* point = new Point;
    point->x = this->x;
    point->y = this->y;
    return point;
}
