#include <allegro5/allegro_color.h>

//NOTE** blast has same struct as ship
typedef struct{
      float x;
      float y;
      float heading;
      float speed;
      int gone;
      ALLEGRO_COLOR color;
} BLAST;

void draw_blast(BLAST *b);
void blast_graphics(BLAST *b);
void calculate_blast_movements(BLAST *b);
BLAST fire_blast();
