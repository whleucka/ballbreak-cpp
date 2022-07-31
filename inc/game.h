#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include "globals.h"
#include "ball.h"

class Game {
private:
  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE* queue;
  ALLEGRO_DISPLAY *disp;
  ALLEGRO_FONT *font;
  bool redraw = false;
  int score = 0;
  Ball* ball;

public:
  Game();
  ~Game();
  void init();
  void loop();
};
