#pragma once

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include "globals.h"

class Player {
private:
  float x, y;
  int width, height;
  int speed = 20;
  int dx = 0;

public:
  Player(float x, float y, int width, int height);
  ~Player();
  void draw();
  void move();
  void left();
  void right();
  void stop();
  bool isMoving();
  Point* getPosition();
};
