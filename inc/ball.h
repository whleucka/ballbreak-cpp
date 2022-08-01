#pragma once

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include "globals.h"

class Ball {
private:
  float speed = 5;
  float r;
  int dx = 1;
  int dy = -1;
public:
  Ball(int x, int y, int r);
  ~Ball();
  float x, y;
  void draw();
  void move();
  void direction();
  bool isMoving();
  Point* getPosition();
};
