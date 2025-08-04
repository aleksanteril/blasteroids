#include "ship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "settings.h"

const int SPEED_MAX = 10;
const int SPEED_MIN = 0;

void ship_graphics(SPACESHIP *ship) {
      al_draw_line(-8, 9, 0, -11, ship->color, 3.0f);
      al_draw_line(0, -11, 8, 9, ship->color, 3.0f);
      al_draw_line(-6, 4, -1, 4, ship->color, 3.0f);
      al_draw_line(6, 4, 1, 4, ship->color, 3.0f);
}

void draw_ship(SPACESHIP *ship) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, ship->heading);
      al_translate_transform(&transform, ship->x, ship->y);
      al_use_transform(&transform);
      ship_graphics(ship);
}


extern int display_x;
extern int display_y;

void calculate_ship_movements(SPACESHIP *ship) {
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

SPACESHIP init_ship() {
      SPACESHIP ship = {20, 20, 0, 0, 0, al_map_rgb(0, 255, 0)};
      return ship;
}
