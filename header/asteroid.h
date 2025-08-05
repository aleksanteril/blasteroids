#include <allegro5/allegro_color.h>

typedef struct Asteroid {
      float x;
      float y;
      float heading;
      float twist;
      float speed;
      float rot_velocity;
      float scale;
      int gone;
      ALLEGRO_COLOR color;
} Asteroid;

void draw_asteroid(Asteroid *a);
void asteroid_graphics(Asteroid *a);
void calculate_asteroid_movements(Asteroid *a);
Asteroid fire_asteroid();
