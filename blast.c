#include "blast.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "ship.h"

void blast_graphics(BLAST *b) {
      al_draw_line(-8, 9, 0, -11, b->color, 3.0f);
}

void draw_blast(BLAST *b) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, b->heading);
      al_translate_transform(&transform, b->x, b->y);
      al_use_transform(&transform);
      blast_graphics(b);
}


extern int display_x;
extern int display_y;

void calculate_blast_movements(BLAST *b) {
      //Y and X movement
      b->x += sin(b->heading) * b->speed;
      b->y -= cos(b->heading) * b->speed;

      b->x = fmod(b->x + display_x, display_x);
      b->y = fmod(b->y + display_y, display_y);
}

BLAST fire_blast(SPACESHIP *ship) {
      BLAST b = {ship->x, ship->y, ship->heading, ship->speed+10, 0, al_map_rgb(255, 0, 0)};
      return b;
}
