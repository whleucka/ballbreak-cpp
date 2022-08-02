#pragma once

#include "globals.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

class Brick {
private:
  float x, y, width, height;
  Colour* colour;
  bool alive = true;

public:
  Brick(float x, float y, float width, float height);
  ~Brick();
  void draw();
  void setColour(float r, float g, float b, float a);
  Point* getPosition();
  bool isAlive() { return alive; }
};
