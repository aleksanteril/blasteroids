#ifndef ASTEROID_H
#define ASTEROID_H

#include <allegro5/allegro_color.h>

typedef struct Asteroid {
      float x;
      float y;
      float heading;
      float twist;
      float speed;
      float rot_velocity;
      float scale;
      float radius;
      int gone;
      ALLEGRO_COLOR color;
      struct Asteroid *next;
} Asteroid;

void draw_asteroid(Asteroid *a);
void calculate_asteroid_movements(Asteroid *a);
Asteroid* create_asteroid(float x, float y);

#endif
