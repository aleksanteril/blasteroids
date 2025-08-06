#include "../header/core.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

//Screen x, and y
const int display_x = 1000;
const int display_y = 1000;

int main()
{     
      //Allegro startup routine
      ALLEGRO_EVENT_QUEUE* queue;
      ALLEGRO_DISPLAY* disp;
      ALLEGRO_TIMER* timer;
      ALLEGRO_EVENT event;
      
      al_init(); // Init allegro
      al_install_keyboard(); //Init keyboard
      al_init_primitives_addon();
      queue = al_create_event_queue(); //Inputs read from player
      disp = al_create_display(display_x, display_y); //Init display
      timer = al_create_timer(1.0 / 60.0); // Game tickrate 30Hz

      /* Register the event queue sources */
      al_register_event_source(queue, al_get_keyboard_event_source());
      al_register_event_source(queue, al_get_display_event_source(disp));
      al_register_event_source(queue, al_get_timer_event_source(timer));

      init_game();

      al_start_timer(timer);
      while (event.type != ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_wait_for_event(queue, &event);
            process_inputs();
            if (event.type != ALLEGRO_EVENT_TIMER)
                  continue;
            update_game_state();
      }
      return 0;
}
