#include "../header/ship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const int SPEED_MAX = 10;
const int SPEED_MIN = 0;

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


extern int display_x;
extern int display_y;

void calculate_ship_movements(Spaceship *ship) {
      //Limits
      //No reverse
      if (ship->speed < SPEED_MIN) 
            ship->speed = SPEED_MIN;
      if (ship->speed > SPEED_MAX)
            ship->speed = SPEED_MAX;

      //Y and X movement
      ship->x += sin(ship->heading) * ship->speed;
      ship->y -= cos(ship->heading) * ship->speed;

      //Boundary check
      ship->x = fmod(ship->x + display_x, display_x);
      ship->y = fmod(ship->y + display_y, display_y);
}

void reset_ship(Spaceship *ship) {
      ship->x = display_x / 2;
      ship->y = display_y / 2;
      ship->speed = 0;
      ship->heading = 0;
      ship->gone = 0;
}

Spaceship* init_ship() {
      Spaceship* ship = malloc(sizeof(Spaceship));
      ship->x = display_x / 2;
      ship->y = display_y / 2;
      ship->speed = 0;
      ship->heading = 0;
      ship->gone = 0;
      ship->radius = 13;
      ship->time_died = 0;
      ship->color = al_map_rgb(0, 255, 0);
      return ship;
}
