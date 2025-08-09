#ifndef CORE_H
#define CORE_H

#include "allegro5/allegro.h"
#define DISPLAY_X 1000
#define DISPLAY_Y 1000

void process_inputs(ALLEGRO_EVENT *event);
void update_game_state();
void init_game();
void cleanup_heap();

#endif
