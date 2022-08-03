#pragma once

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <iostream>
#include "globals.h"
#include "player.h"

class Ball {
private:
  float speed = 4;
  float x, y, r;
  float dx = 1;
  float dy = -1;
public:
  Ball(Player* player, float r);
 ~Ball();
  bool active = false;
  void draw();
  void move();
  void direction();
  bool isMoving();
  Point* getPosition();
  float getSpeed() { return speed; }
  float getRadius() { return r; }
  bool isActive() { return active; }
  bool isSouth() { return dy > 0; }
  bool isEast() { return dx < 0; }
  void changeDirection(float dx = 0, float dy = 0);
  void setActive(bool active) { this->active = active; }
  Player* player;
};
