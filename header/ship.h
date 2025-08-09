#ifndef SHIP_H
#define SHIP_H

#include <allegro5/allegro_color.h>

/* Ship limits */
#define MAX_SPEED 10
#define MIN_SPEED 0

typedef struct Spaceship{
      float x;
      float y;
      float heading;
      float speed;
      float radius;
      double time_died;
      int gone;
      ALLEGRO_COLOR color;
} Spaceship;

void draw_ship(Spaceship *ship);
void calculate_ship_movements(Spaceship *ship);
void reset_ship(Spaceship *ship);
Spaceship* init_ship();

#endif
