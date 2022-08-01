#pragma once

#include "globals.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

class Brick {
private:
  float x, y;
  int width, height;
  Colour* colour;

public:
  Brick();
  ~Brick();
  void draw();
  void setColour(float r, float g, float b, float a);
};
