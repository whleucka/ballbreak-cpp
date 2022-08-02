#pragma once

#include "ball.h"
#include "brick.h"
#include "globals.h"
#include "player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <iostream>
#include <stdbool.h>
#include <vector>
#include <math.h>

class Game {
private:
  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_DISPLAY *disp;
  ALLEGRO_FONT *font;
  bool redraw = false;
  bool running = true;
  bool paused = false;
  int score = 0;
  int life = 4;
  Ball *ball;
  Player *player;
  std::vector<Brick *> bricks;
  void init();
  void loop();
  void detectCollisions();
  void loadBricks();

public:
  Game();
  ~Game();
};
