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
    al_draw_filled_circle(x, y, width, al_map_rgba(colour->r, colour->g, colour->b, colour->a));
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
