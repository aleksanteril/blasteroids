#include <allegro5/allegro_color.h>

typedef struct Spaceship Spaceship;

typedef struct Blast {
      float x;
      float y;
      float heading;
      float speed;
      int gone;
      ALLEGRO_COLOR color;
} Blast;

void draw_blast(Blast *b);
void blast_graphics(Blast *b);
void calculate_blast_movements(Blast *b);
Blast* fire_blast(Spaceship *ship);
