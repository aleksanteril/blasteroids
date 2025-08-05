#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../header/ship.h"
#include "../header/blast.h"
#include <stdio.h>


//Screen x, and y
const int display_x = 1000;
const int display_y = 1000;
Blast *b = NULL;

void process_inputs(ALLEGRO_EVENT *event, Spaceship *ship) {

      ALLEGRO_KEYBOARD_STATE state;
      al_get_keyboard_state(&state);

      //Heading change is a function of the ship's speed -0.005*spd and a base of 0.1
      if (al_key_down(&state, ALLEGRO_KEY_LEFT)) {
            ship->heading -= (-0.005*ship->speed+0.1);
      }
      else if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) {
            ship->heading += (-0.005*ship->speed+0.1);
      }

      if (event->type != ALLEGRO_EVENT_KEY_DOWN)
            return;
      switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                  ship->speed += 1;
                  break;
            case ALLEGRO_KEY_DOWN:
                  ship->speed -= 1;
                  break;
            case ALLEGRO_KEY_SPACE:
                  b = fire_blast(ship);
                  break;
            default:
                  break;
      }
}


void process_screen(Spaceship *ship, Blast *b) {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      draw_ship(ship);
      if (b) draw_blast(b);
      al_flip_display();
}

void process_physics(Spaceship *ship, Blast *b) {
      calculate_ship_movements(ship);
      if (!b) 
            return;
      calculate_blast_movements(b);
}

void destroy_objects(Spaceship *ship, Blast *b) {
      if (b->gone) 
            free(b);
      if (ship->gone) {
            //Lives -1,
            ship->x = display_x/2;
            ship->y = display_y/2;
      }
}

int main()
{     
      /* Initial start here */

      al_init(); // Init allegro
      al_install_keyboard(); //Init keyboard
      al_init_primitives_addon();
      ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Inputs read from player
      ALLEGRO_DISPLAY* disp = al_create_display(display_x, display_y); //Init display
      ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); // Game tickrate 30Hz

      /* Register the event queue sources */
      al_register_event_source(queue, al_get_keyboard_event_source());
      al_register_event_source(queue, al_get_display_event_source(disp));
      al_register_event_source(queue, al_get_timer_event_source(timer));

      //Event struct
      ALLEGRO_EVENT event;

      //Create player:
      Spaceship ship;
      ship = init_ship();

      al_start_timer(timer); //Start ticks
      while (event.type != ALLEGRO_EVENT_DISPLAY_CLOSE) {
            printf("Ship speed: %f, heading: %f | x: %f, y %f\n", ship.speed, ship.heading, ship.x, ship.y);
            al_wait_for_event(queue, &event);
            process_inputs(&event, &ship);
            if (event.type != ALLEGRO_EVENT_TIMER)
                  continue;
            process_physics(&ship, b);
            process_screen(&ship, b);
      } //Exit when display X pressed
      return 0;
}
