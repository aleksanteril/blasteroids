#include "../header/core.h"
#include "../header/ship.h"
#include "../header/blast.h"
#include "../header/asteroid.h"
#include "../header/utilities.h"
#include "../header/hud.h"
#include <math.h>

//Linked lists here to iterate over, to draw and calculate physics
static Asteroid* asteroid_head = NULL;
static Blast* blast_head = NULL;
static Spaceship* ship;

extern int score;
extern int lives;

/* KOODI DUPLIKAATIOTA VOIDAAN VÄHENTÄÄ MACROILLA?*/
void generate_asteroid() {
      float x = (float)randint(0, DISPLAY_X);
      float y = (float)randint(0, DISPLAY_Y);
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
      float x_apart;
      float y_apart;
      float distance_squared;
      float radius_sum;

      Blast *b = blast_head;
      Asteroid *a = asteroid_head;
      //Detect bullet collisions with asteroids
      while (b) {
            while(a) {
                  x_apart = b->x - a->x;
                  y_apart = b->y - a->y;
                  radius_sum = b->radius + a->radius;

                  //Bounding box check
                  if (fabs(x_apart) > radius_sum || fabs(y_apart) > radius_sum) {
                        a = a->next;
                        continue;
                  }

                  //circle radii check
                  distance_squared = x_apart * x_apart + y_apart * y_apart;
                  if (distance_squared < radius_sum * radius_sum) {
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
      

      //If just died invicibility still on
      if ((al_get_time() - ship->time_died) < 5)
            return;

      a = asteroid_head;
      //Detect ship collision with asteroids
      while(a) {
            x_apart = ship->x - a->x;
            y_apart = ship->y - a->y;
            radius_sum = ship->radius + a->radius;

            //Bounding box check
            if (fabs(x_apart) > radius_sum || fabs(y_apart) > radius_sum) {
                  a = a->next;
                  continue;
            }

            //Circle radii check
            distance_squared = x_apart * x_apart + y_apart * y_apart;
            if (distance_squared < radius_sum * radius_sum) {
                  ship->gone = 1;
                  ship->time_died = al_get_time();
                  break;
            }
            a = a->next;
      }
}

//Cleanup for example on game exit
void cleanup_heap() {

      while(asteroid_head) {
            Asteroid *temp = asteroid_head;
            asteroid_head = asteroid_head->next;
            free(temp);
      }

      while(blast_head) {
            Blast *temp = blast_head;
            blast_head = blast_head->next;
            free(temp);
      }

      if (ship) {
            free(ship);
            ship = NULL;
      }

}

void process_inputs(ALLEGRO_EVENT *event) {
      static ALLEGRO_KEYBOARD_STATE state;
      if (ship->gone)
            return;

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
      draw_hud();
      al_flip_display();
}

void physics_loop() {
      collision_detection();
      calculate_ship_movements(ship);
      calculate_object_mov();
}

void init_game() {
      ship = init_ship();
      init_hud();
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
