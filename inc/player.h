#pragma once

#include "globals.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

class Player {
private:
  float x, y, width, height;
  int speed = 20;
  int dx = 0;

public:
  Player(float x, float y, float width, float height);
  ~Player();
  void draw();
  void move();
  void left();
  void right();
  void stop();
  bool isMoving();
  Point *getPosition();
  float getWidth() { return width; }
  float getHeight() { return height; }
};
