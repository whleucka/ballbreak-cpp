#include "player.h"

Player::Player(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Player::~Player() {
}

void Player::draw() {
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y + height;
    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgba(255, 15, 15, 255));
}

void Player::left() {
    dx = -1;
}

void Player::right() {
    dx = 1;
}

void Player::stop() {
    dx = 0;
}

bool Player::isMoving() {
    return dx != 0;
}

void Player::move() {
    // If dx == 0, we aren't moving
    if (dx != 0) {
        // Moving left or right
        x = x + speed * dx;

        // Detect off left-side of the screen
        if (x < 0)
            x = 0;

        // Detect off right-side of the screen
        if (x + width > SCREEN_WIDTH)
            x = SCREEN_WIDTH - width;
    }
}

Point* Player::getPosition() {
    Point* point = new Point;
    point->x = this->x;
    point->y = this->y;
    return point;
}
