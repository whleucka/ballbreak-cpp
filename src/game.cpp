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
    // Ball hits player
    Point* ball_pos = ball->getPosition();
    Point* player_pos = player->getPosition();

    std::cout << "ball: " << ball_pos->x << " " << ball_pos->y << std::endl;
    std::cout << "player: " << player_pos->x << " " << player_pos->y << std::endl;

    delete(ball_pos);
    delete(player_pos);
}

void Game::loop() {
    ALLEGRO_EVENT event;
    ball = new Ball(100,600,5);
    player = new Player((SCREEN_WIDTH / 2) - 70, 720, 140, 10);

    bool running = true;
    bool paused = false;

    while (running) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
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
                case ALLEGRO_KEY_ESCAPE:
                    running = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                    player->left();
                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
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

            /* Display score / level
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "SCORE n/a");
            al_draw_text(font, al_map_rgb(255, 255, 255), 100, 0, 0, "LEVEL n/a");
            */

            // Move ball / player
            if (!paused) {
                ball->move();
                player->move();
                detectCollisions();
            }

            // Draw ball / player / bricks
            ball->draw();
            player->draw();
            
            al_flip_display();
            redraw = false;
        }
    }
}
