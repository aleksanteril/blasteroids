#include "../header/core.h"
#include "../header/ship.h"
#include "../header/blast.h"
#include "../header/asteroid.h"
#include "../header/utilities.h"
#include <math.h>

//Linked lists here to iterate over, to draw and calculate physics
static Asteroid* asteroid_head = NULL;
static Blast* blast_head = NULL;
static Spaceship* ship;

extern int display_x;
extern int display_y;

extern int score;
extern int lives;

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

void split_asteroid(Asteroid *a) {
      Asteroid *part2 = create_asteroid(a->x, a->y);
      part2->scale = 0.99;
      a->scale = 0.99;
      a->gone = 0; //Reset the gone flag from the 1st
      part2->next = a->next;
      a->next = part2;
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

void cleanup_objects() {
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


      Asteroid **as_current = &asteroid_head;
      Asteroid *as_to_delete;
      //This works by anchoring to the head and traversing the list through head->next, never leaving "head"
      while (*as_current) {
            if ((*as_current)->gone) {
                  //Split asteroid if it is big
                  if((*as_current)->scale < 1) {
                        as_to_delete = *as_current;
                        *as_current = (*as_current)->next;
                        free(as_to_delete);
                        continue;
                  }
                  split_asteroid((*as_current));
            }
            as_current = &((*as_current)->next);
      }

      //Ship reset if dead, Need to make a invincibility timer of 5s when died
      if (ship->gone) {
            lives -= 1;
            reset_ship(ship);
      }

}

void draw_objects() {
      Asteroid *i = asteroid_head;
      while (i) {
            draw_asteroid(i);
            i = i->next;
      }

      Blast *j = blast_head;
      while (j) {
            draw_blast(j);
            j = j->next;
      }
}

void calculate_object_mov() {
      Asteroid *i = asteroid_head;
      while (i) {
            calculate_asteroid_movements(i);
            i = i->next;
      }

      Blast *j = blast_head;
      while (j) {
            calculate_blast_movements(j);
            j = j->next;
      }
}
/* KOODI DUPLIKAATIOTA VOIDAAN VÄHENTÄÄ MACROILLA?*/

void collision_detection() {
      double x_apart;
      double y_apart;
      double distance;

      Blast *b = blast_head;
      Asteroid *a = asteroid_head;
      //Detect bullet collisions with asteroids
      while (b) {
              while(a) {
                  x_apart = b->x - a->x;
                  y_apart = b->y - a->y;
                  distance = sqrt(pow(x_apart, 2) + pow(y_apart, 2));

                  //Collision bullet and asteroid
                  if (distance < (b->radius + a->radius)) {
                        b->gone = 1;
                        a->gone = 1;
                        score += 100;
                        break; //Bullet destroyed move to next
                  }
                  a = a->next;
            }
            a = asteroid_head; //Reset head
            b = b->next; //Next bullet
      }
      

      //5second invicibility
      
      a = asteroid_head;
      //Detect ship collision with asteroids
      while(a) {
            x_apart = ship->x - a->x;
            y_apart = ship->y - a->y;
            distance = sqrt(pow(x_apart, 2) + pow(y_apart, 2));

            //Collision
            if (distance < (ship->radius + a->radius)) {
                  ship->gone = 1;
            }
            a = a->next;
      }
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

void draw_loop() {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      draw_ship(ship);
      draw_objects();
      al_flip_display();
}

void physics_loop() {
      collision_detection();
      calculate_ship_movements(ship);
      calculate_object_mov();
}

void init_game() {
      ship = init_ship();
      for (int i = 0; i < 20; i++) {
            generate_asteroid();
      }
      draw_loop(); //Initial draw of the game
}

void update_game_state() {
      cleanup_objects();
      physics_loop();
      draw_loop();
}
