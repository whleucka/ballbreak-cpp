#include "brick.h"

Brick::Brick() {
}

Brick::~Brick() {
    delete(colour);
}

void Brick::draw() {
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y + height;
    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgba(255, 255, 255, 255));
}

void Brick::setColour(float r, float g, float b, float a) {
    colour = new Colour;
    colour->r = r;
    colour->g = g;
    colour->b = b;
    colour->a = a;
}
