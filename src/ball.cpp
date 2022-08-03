#include "ball.hpp"

Ball::Ball(Player* player, float r) {
    this->player = player;
    this->r = r;
}

Ball::~Ball() {
}

void Ball::draw() {
    al_draw_filled_circle(x, y, r, al_map_rgba(255, 255, 255, 255));
}

void Ball::move() {
    if (!active) {
        Point* player_pos = player->getPosition();
        x = player_pos->x + player->getWidth() / 2;
        y = player_pos->y - r;
    } else {
        direction();
        x = x + speed * dx;
        y = y + speed * dy;
    }

}

bool Ball::isMoving() {
    return dx != 0 && dy != 0;
}

void Ball::direction() {
    // Ball direction heading north, east, south, west
    if (x + speed >= SCREEN_WIDTH) {
        dx = dx * -1;
    } else if (x - speed <= 0) {
        dx = dx * -1;
    }
    if (y + speed >= SCREEN_HEIGHT) {
        dy = dy * -1;
    } else if (y - speed <= 0) {
        dy = dy * -1;
    }
}

Point* Ball::getPosition() {
    Point* point = new Point;
    point->x = this->x;
    point->y = this->y;
    return point;
}

void Ball::changeDirection(float dx, float dy) {
    if (dx != 0.0f) 
        this->dx = dx;
    if (dy != 0.0f) 
        this->dy = dy;
}
