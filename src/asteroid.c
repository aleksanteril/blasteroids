#include "../header/asteroid.h"
#include "../header/utilities.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

void asteroid_graphics(Asteroid *a) {
      al_draw_line(-20, 20, -25, 5, a->color, 3.0f);
      al_draw_line(-25, 5, -25, -10, a->color, 3.0f);
      al_draw_line(-25, -10, -5, -10, a->color, 3.0f);
      al_draw_line(-5, -10, -10, -20, a->color, 3.0f);
      al_draw_line(-10, -20, 5, -20, a->color, 3.0f);
      al_draw_line(5, -20, 20, -10, a->color, 3.0f);
      al_draw_line(20, -10, 20, -5, a->color, 3.0f);
      al_draw_line(20, -5, 0, 0, a->color, 3.0f);
      al_draw_line(0, 0, 20, 10, a->color, 3.0f);
      al_draw_line(20, 10, 10, 20, a->color, 3.0f);
      al_draw_line(10, 20, 0, 15, a->color, 3.0f);
      al_draw_line(0, 15, -20, 20, a->color, 3.0f);
}

void draw_asteroid(Asteroid *a) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_scale_transform(&transform, a->scale, a->scale);
      al_rotate_transform(&transform, a->twist);
      al_translate_transform(&transform, a->x, a->y);
      al_use_transform(&transform);
      asteroid_graphics(a);
}


extern int display_x;
extern int display_y;

void calculate_asteroid_movements(Asteroid *a) {
      //Y and X movement
      a->x += sin(a->heading) * a->speed;
      a->y -= cos(a->heading) * a->speed;

      //Rotation
      a->twist += a->rot_velocity;

      //Boundary check
      a->x = fmod(a->x + display_x, display_x);
      a->y = fmod(a->y + display_y, display_y);
}

Asteroid* create_asteroid(float x, float y) {
      Asteroid *a = malloc(sizeof(Asteroid));
      a->x = x;
      a->y = y;
      a->heading = randint(1, 628)*0.01; //Values between 0.01 - 6.28
      a->speed = randint(10, 20)*0.1; //Between 1-3
      a->rot_velocity = randint(1, 50)*0.001; //Between 0.001-0.05
      a->scale = 1.5;
      a->twist = 0;
      a->gone = 0;
      a->color = al_map_rgb(250, 250, 255);
      a->next = NULL;
      return a;
}
