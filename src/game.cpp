#include "game.h"
#include "globals.h"

Game::Game() {
    // Set up the game and run the loop
    init();
    loop();
}

Game::~Game() {
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    bricks.clear();
    delete(ball);
    delete(player);
}

void Game::init() {
    al_init();
    al_install_keyboard();
    al_install_mouse();

    timer = al_create_timer(1.0 / FPS);
    queue = al_create_event_queue();
    disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
}

void Game::detectCollisions() {
    Point* ball_pos = ball->getPosition();
    Point* player_pos = player->getPosition();
     
    // Ball hits brick
    // This is where is could be a bit tricky
    int brick_count = bricks.size();
    int dead_bricks = 0;
    for (Brick* brick: bricks) {
        if (brick->isAlive()) {
            Point* brick_pos = brick->getPosition();
            float ball_x = ball->isEast()
                ? ball_pos->x + ball->getRadius() + ball->getSpeed()
                : ball_pos->x - ball->getRadius() + ball->getSpeed();
            float ball_y = ball->isSouth()
                ? ball_pos->y + ball->getRadius() + ball->getSpeed()
                : ball_pos->y - ball->getRadius() + ball->getSpeed();
            if (ball_x >= brick_pos->x && ball_x <= brick_pos->x + brick->getWidth() &&
                    ball_y >= brick_pos->y && ball_y <= brick_pos->y + brick->getHeight()) {

                // Figure out bounce
                float ball_dx = 0;
                float ball_dy = 0;
                float brick_x = ball->isEast()
                    ? brick_pos->x
                    : brick_pos->x + brick->getWidth();

                if (ball_pos->x + ball->getSpeed() < brick_x) {
                    ball_dx = ball->isEast()
                        ? -1
                        : 1;
                } else {
                    ball_dy = ball->isSouth()
                        ? -1
                        : 1;
                }

                ball->changeDirection(ball_dx, ball_dy);
                brick->kill();
                if (ball->isActive()) {
                    // Player accumulates points when ball is active
                    score += 1000;
                }
                break;
            }
        } else {
            dead_bricks++;
        }
    }
    // Level cleared
    if (dead_bricks == brick_count) {
        level++;
        score += 10000;
        ball->setActive(false);
        bricks.clear();
        loadBricks();
    }

    if (ball->isSouth()) {
        // Ball hits player
        // Match y coordinate
        if (ball_pos->y + ball->getRadius() >  player_pos->y &&
                ball_pos->y + ball->getRadius() < player_pos->y + player->getHeight()) {
            // Match x coordinate
            if (ball_pos->x + ball->getRadius() > player_pos->x &&
                    ball_pos->x + ball->getRadius() < player_pos->x + player->getWidth()) {
                // Bounce ball upwards
                ball->changeDirection(0, -1);
            }
        }

        // Ball hits the floor :(
        if (ball_pos->y + ball->getRadius() >= SCREEN_HEIGHT) {
            // Lose a life
            life--;
            // Player accumulates points when ball is active
            score -= 250;
            // Check end of game state
            if (life < 0) {
                running = false;
                std::cout << "Game over..." << std::endl;
                std::cout << "Final score: " << score << std::endl;
            }

            ball->setActive(false);
        }
    }
}

void Game::loadBricks() {
    srand(time(NULL)); // Seed the random
    float colour_random = rand()%(255-0 + 1) + 0;
    float start_x = 60;
    float start_y = 50;
    float width = 30;
    float height = 12;
    int cols = std::floor((SCREEN_WIDTH - start_x - width * 2) / width);
    int rows = std::min(level, 50);
    for (int h = 0; h < rows; h++) {
        for (int i = 0; i < cols; i++) {
            float x = start_x + (width * i);
            float y = start_y + (height * h);
            Brick* b = new Brick(x, y, width, height);
            b->setColour(255, colour_random, int(i*h*colour_random) % 255, 100);
            bricks.push_back(b);
        }
    }
}

void Game::loop() {
    ALLEGRO_EVENT event;
    player = new Player((SCREEN_WIDTH / 2) - 60, 720, 120, 10);
    ball = new Ball(player, 5);
    loadBricks();

    while (running) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            if (ball->isActive()) {
                // Player accumulates points when ball is active
                score += 2;
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_D:
                    player->stop();
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    ball->setActive(true);
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    running = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_J:
                    player->left();
                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                case ALLEGRO_KEY_L:
                    player->right();
                    break;
                case ALLEGRO_KEY_PAUSE:
                case ALLEGRO_KEY_P:
                    paused = !paused;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            // Mouse stuff...
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Display score / level
            char the_score[50];
            char the_level[50];
            char the_lives[50];
            sprintf(the_score, "SCORE %d", score);
            sprintf(the_level, "LEVEL %d", level);
            sprintf(the_lives, "LIVES %d", life);
            al_draw_text(font, al_map_rgb(255, 255, 255), 25, SCREEN_HEIGHT - 10, 0, the_lives);
            al_draw_text(font, al_map_rgb(255, 255, 255), 100, SCREEN_HEIGHT - 10, 0, the_level);
            al_draw_text(font, al_map_rgb(255, 255, 255), 175, SCREEN_HEIGHT - 10, 0, the_score);
            

            // Move ball / player
            if (!paused) {
                detectCollisions();
                ball->move();
                player->move();
            }

            // Draw ball / player / bricks
            for (Brick* brick: bricks) {
                if (brick->isAlive())
                    brick->draw();
            }
            ball->draw();
            player->draw();
            
            al_flip_display();
            redraw = false;
        }
    }
}
