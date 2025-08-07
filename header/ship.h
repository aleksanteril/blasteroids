#include <allegro5/allegro_color.h>

typedef struct Spaceship{
      float x;
      float y;
      float heading;
      float speed;
      int gone;
      ALLEGRO_COLOR color;
} Spaceship;

void draw_ship(Spaceship *ship);
void calculate_ship_movements(Spaceship *ship);
Spaceship* init_ship();
