#pragma once

#include "globals.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

class Ball {
private:
  float speed = 5;
  float x, y, r;
  int dx = 1;
  int dy = -1;

public:
  Ball(int x, int y, int r);
  ~Ball();
  void draw();
  void move();
  void direction();
};
