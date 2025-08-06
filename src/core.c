#include "../header/core.h"
#include "../header/ship.h"
#include "../header/blast.h"
#include "../header/asteroid.h"

//Linked lists here to iterate over, to draw and calculate physics
static Spaceship* ship;
static ALLEGRO_KEYBOARD_STATE state;
//void add_object_to_list
//void remove_object_from_list

//Screen x, and y
extern int display_x;
extern int display_y;

void draw_loop() {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      draw_ship(ship);
      al_flip_display();
}

void physics_loop() {
      calculate_ship_movements(ship);
}

void process_inputs() {
      al_get_keyboard_state(&state);

      //Heading change is a function of the ship's speed -0.005*spd and a base of 0.1
      if (al_key_down(&state, ALLEGRO_KEY_LEFT)) {
            ship->heading -= (-0.007*ship->speed+0.1);
      }
      else if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) {
            ship->heading += (-0.007*ship->speed+0.1);
      }

      if (al_key_down(&state, ALLEGRO_KEY_UP)) {
            ship->speed += 0.2; // Smaller increment for smooth acceleration
      }
      if (al_key_down(&state, ALLEGRO_KEY_DOWN)) {
            ship->speed -= 0.2;
      }
      if (al_key_down(&state, ALLEGRO_KEY_SPACE)) {
            // Handle firing with rate limiting
      }
}

void init_game() {
      ship = init_ship();
      draw_loop(); //Initial draw of the game
}

void collision_detection() {
      //Detect collisions here and change object->gone = 1
}

void destroy_object() {
      //Iterate over and if(obj->gone) free(obj) set to null;
}

void update_game_state() {
      physics_loop();
      draw_loop();
}
