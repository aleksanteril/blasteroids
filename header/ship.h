#include <allegro5/allegro_color.h>

typedef struct Spaceship{
      float x;
      float y;
      float heading;
      float speed;
      float radius;
      int gone;
      ALLEGRO_COLOR color;
} Spaceship;

void draw_ship(Spaceship *ship);
void calculate_ship_movements(Spaceship *ship);
void reset_ship(Spaceship *ship);
Spaceship* init_ship();
