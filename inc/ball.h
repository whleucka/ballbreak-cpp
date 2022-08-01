#pragma once

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include "globals.h"
#include "player.h"

class Ball {
private:
  float speed = 5;
  float x, y, r;
  int dx = 1;
  int dy = -1;
public:
  Ball(Player* player, float r);
 ~Ball();
  bool active = false;
  void draw();
  void move();
  void direction();
  bool isMoving();
  Point* getPosition();
  float getRadius() { return r; }
  bool isActive() { return active; }
  bool isSouth() { return dy == 1; }
  bool isEast() { return dx == 1; }
  void changeDirection(int dx = 0, int dy = 0);
  void setActive(bool active) { this->active = active; }
  Player* player;
};
