#include "../header/core.h"
#include "../header/ship.h"
#include "../header/blast.h"
#include "../header/asteroid.h"
#include "../header/utilities.h"

//Linked lists here to iterate over, to draw and calculate physics
static Asteroid* asteroid_head = NULL;
static Blast* blast_head = NULL;

static Spaceship* ship;

extern int display_x;
extern int display_y;

/* KOODI DUPLIKAATIOTA VOIDAAN VÄHENTÄÄ MACROILLA?*/
void generate_asteroid() {
      float x = (float)randint(0, display_x);
      float y = (float)randint(0, display_y);
      Asteroid *a = create_asteroid(x, y);

      //Creating first case, assign to head.
      if (!asteroid_head) {
            asteroid_head = a;
            return;
      }

      // Insert new asteroid at the head of the linked list
      a->next = asteroid_head;
      asteroid_head = a;
}

void generate_blast() {
      Blast *b = fire_blast(ship);

      //Creating first case, assign to head.
      if (!blast_head) {
            blast_head = b;
            return;
      }

      // Insert new blast at the head of the linked list
      b->next = blast_head;
      blast_head = b;
}

void cleanup_asteroids() {
      Asteroid **current = &asteroid_head;
      Asteroid *to_delete;

      //This works by anchoring to the head and traversing the list through head->next, never leaving "head"
      while (*current) {
            if ((*current)->gone) {
                  to_delete = *current;
                  *current = (*current)->next;
                  free(to_delete);
                  continue;
            }
            current = &((*current)->next);
      }
}

void cleanup_blasts() {
      Blast **current = &blast_head;
      Blast *to_delete;

      while (*current) {
            if ((*current)->gone) {
                  to_delete = *current;
                  *current = (*current)->next;
                  free(to_delete);
                  continue;
            }
            current = &((*current)->next);
      }
}

void draw_asteroids() {
      Asteroid *i = asteroid_head;
      while (i) {
            draw_asteroid(i);
            i = i->next;
      }
}

void draw_blasts() {
      Blast *i = blast_head;
      while (i) {
            draw_blast(i);
            i = i->next;
      }
}

void calculate_asteroids() {
      Asteroid *i = asteroid_head;
      while (i) {
            calculate_asteroid_movements(i);
            i = i->next;
      }
}

void calculate_blasts() {
      Blast *i = blast_head;
      while (i) {
            calculate_blast_movements(i);
            i = i->next;
      }
}
/* KOODI DUPLIKAATIOTA VOIDAAN VÄHENTÄÄ MACROILLA?*/


void draw_loop() {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      draw_ship(ship);
      draw_asteroids();
      draw_blasts();
      al_flip_display();
}

void physics_loop() {
      calculate_ship_movements(ship);
      calculate_asteroids();
      calculate_blasts();
}


static ALLEGRO_KEYBOARD_STATE state;
void process_inputs(ALLEGRO_EVENT *event) {
      al_get_keyboard_state(&state);

      //Heading change is a function of the ship's speed -0.005*spd and a base of 0.1
      if (al_key_down(&state, ALLEGRO_KEY_LEFT))
            ship->heading -= (-0.007*ship->speed+0.1);

      else if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) 
            ship->heading += (-0.007*ship->speed+0.1);

      if (al_key_down(&state, ALLEGRO_KEY_UP))
            ship->speed += 0.2; // Smaller increment for smooth acceleration

      if (al_key_down(&state, ALLEGRO_KEY_DOWN))
            ship->speed -= 0.2;
      
      if ((event->type == ALLEGRO_EVENT_KEY_DOWN) && (event->keyboard.keycode == ALLEGRO_KEY_SPACE))
            generate_blast();
}

void init_game() {
      ship = init_ship();
      for (int i = 0; i < 20; i++) {
            generate_asteroid();
      }
      draw_loop(); //Initial draw of the game
}

void collision_detection() {
      //Detect collisions here and change object->gone = 1
}

void destroy_object() {
      //Iterate over and if(obj->gone) free(obj) set to null;
}

void update_game_state() {
      cleanup_asteroids();
      cleanup_blasts();
      physics_loop();
      draw_loop();
}
