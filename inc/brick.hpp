#pragma once

#include "globals.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

class Brick {
private:
  float x, y, r;
  Colour *colour;
  bool alive = true;

public:
  Brick(float x, float y, float r);
  ~Brick();
  void draw();
  void setColour(float r, float g, float b, float a);
  Point *getPosition();
  bool isAlive() { return alive; }
  float getRadius() { return r; }
  void kill() { alive = false; }
};
