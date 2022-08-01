#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <iostream>
#include <stdbool.h>
#include "globals.h"
#include "ball.h"
#include "player.h"

class Game {
private:
  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE* queue;
  ALLEGRO_DISPLAY *disp;
  ALLEGRO_FONT *font;
  bool redraw = false;
  int score = 0;
  Ball* ball;
  Player* player;

public:
  Game();
  ~Game();
  void init();
  void loop();
  void detectCollisions();
};
