#include "../header/blast.h"
#include "../header/ship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

void blast_graphics(Blast *b) {
      al_draw_line(0, -11, 0, -16, b->color, 3.0f);
}

void draw_blast(Blast *b) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, b->heading);
      al_translate_transform(&transform, b->x, b->y);
      al_use_transform(&transform);
      blast_graphics(b);
}


extern int display_x;
extern int display_y;

void calculate_blast_movements(Blast *b) {
      //Y and X movement
      b->x += sin(b->heading) * b->speed;
      b->y -= cos(b->heading) * b->speed;

      if ((b->x > display_x) || (b->x < 0))
            b->gone = 1;
      else if ((b->y > display_y) || (b->y < 0))
            b->gone = 1;
}

Blast* fire_blast(Spaceship *ship) {
      Blast *b = malloc(sizeof(Blast));
      b->x = ship->x;
      b->y = ship->y;
      b->heading = ship->heading;
      b->speed = 20;
      b->gone = 0;
      b->color = al_map_rgb(255, 0, 0);
      return b;
}
