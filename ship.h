#include <allegro5/allegro_color.h>

typedef struct{
      float x;
      float y;
      float heading;
      float speed;
      int gone;
      ALLEGRO_COLOR color;
} SPACESHIP;

void draw_ship(SPACESHIP *ship);
void ship_graphics(SPACESHIP *ship);
void calculate_ship_movements(SPACESHIP *ship);
SPACESHIP init_ship();
