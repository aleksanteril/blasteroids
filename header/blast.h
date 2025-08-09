#ifndef BLAST_H
#define BLAST_H

#include <allegro5/allegro_color.h>

typedef struct Spaceship Spaceship;

typedef struct Blast {
      float x;
      float y;
      float heading;
      float speed;
      float radius;
      int gone;
      ALLEGRO_COLOR color;
      struct Blast *next;
} Blast;

void draw_blast(Blast *b);
void calculate_blast_movements(Blast *b);
Blast* fire_blast(Spaceship *ship);

#endif
