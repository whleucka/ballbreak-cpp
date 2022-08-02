#include "brick.h"

Brick::Brick(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Brick::~Brick() {
}

void Brick::draw() {
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y + height;
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgba(255, 255, 255, 255), 1);
}

void Brick::setColour(float r, float g, float b, float a) {
    colour = new Colour;
    colour->r = r;
    colour->g = g;
    colour->b = b;
    colour->a = a;
}

Point* Brick::getPosition() {
    Point* point = new Point;
    point->x = this->x;
    point->y = this->y;
    return point;
}
