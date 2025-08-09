#include "../header/ship.h"
#include "../header/core.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

void ship_graphics(Spaceship *ship) {
      al_draw_line(-8, 9, 0, -11, ship->color, 3.0f);
      al_draw_line(0, -11, 8, 9, ship->color, 3.0f);
      al_draw_line(-6, 4, -1, 4, ship->color, 3.0f);
      al_draw_line(6, 4, 1, 4, ship->color, 3.0f);
      //al_draw_circle(0, 0, ship->radius, al_map_rgb(255, 0, 0), 3.0f);
}

void draw_ship(Spaceship *ship) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, ship->heading);
      al_translate_transform(&transform, ship->x, ship->y);
      al_use_transform(&transform);
      ship_graphics(ship);
}

void calculate_ship_movements(Spaceship *ship) {
      //Limits
      //No reverse
      if (ship->speed < MIN_SPEED) 
            ship->speed = MIN_SPEED;
      if (ship->speed > MAX_SPEED)
            ship->speed = MAX_SPEED;

      //Y and X movement
      ship->x += sin(ship->heading) * ship->speed;
      ship->y -= cos(ship->heading) * ship->speed;

      //Boundary check
      ship->x = fmod(ship->x + DISPLAY_X, DISPLAY_X);
      ship->y = fmod(ship->y + DISPLAY_Y, DISPLAY_Y);
}

void reset_ship(Spaceship *ship) {
      ship->x = DISPLAY_X / 2;
      ship->y = DISPLAY_Y / 2;
      ship->speed = 0;
      ship->heading = 0;
      ship->gone = 0;
}

Spaceship* init_ship() {
      Spaceship* ship = malloc(sizeof(Spaceship));
      ship->x = DISPLAY_X / 2;
      ship->y = DISPLAY_Y / 2;
      ship->speed = 0;
      ship->heading = 0;
      ship->gone = 0;
      ship->radius = 13;
      ship->time_died = 0;
      ship->color = al_map_rgb(0, 255, 0);
      return ship;
}
