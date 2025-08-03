#include <allegro5/allegro.h>



int main()
{     
      /* Initial start here */

      al_init(); // Init allegro
      al_install_keyboard(); //Init keyboard
      ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Inputs read from player
      ALLEGRO_DISPLAY* disp = al_create_display(320, 200); //Init display
      ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); // Game tickrate 30Hz

      /* Register the event queue sources */
      al_register_event_source(queue, al_get_keyboard_event_source());
      al_register_event_source(queue, al_get_display_event_source(disp));
      al_register_event_source(queue, al_get_timer_event_source(timer));
      
      return 0;
}
