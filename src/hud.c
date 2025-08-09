#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../header/hud.h"
#include "../header/core.h"

static ALLEGRO_FONT *font;
static ALLEGRO_COLOR text_color;

extern int score;
extern int lives;

void hud_graphics() {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, 0);
      al_scale_transform(&transform, 3, 3);
      al_translate_transform(&transform, 40, 60);
      al_use_transform(&transform);
      al_draw_textf(font, text_color, 0, 0, ALLEGRO_ALIGN_LEFT, "SCORE: %i", score);
}

void lives_graphics(float offset) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, 0);
      al_scale_transform(&transform, 3, 3);
      al_translate_transform(&transform, 60+offset, 140);
      al_use_transform(&transform);
      al_draw_line(-8, 9, 0, -11, text_color, 3.0f);
      al_draw_line(0, -11, 8, 9, text_color, 3.0f);
      al_draw_line(-6, 4, -1, 4, text_color, 3.0f);
      al_draw_line(6, 4, 1, 4, text_color, 3.0f);
}

void draw_game_over() {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, 0);
      al_scale_transform(&transform, 5, 5);
      al_translate_transform(&transform, DISPLAY_X/4, DISPLAY_Y/4);
      al_use_transform(&transform);
      al_draw_text(font, text_color, 10, 0, ALLEGRO_ALIGN_LEFT, "GAME OVER");
      al_draw_textf(font, text_color, -10, 10, ALLEGRO_ALIGN_LEFT, "FINAL SCORE: %i", score);
      al_flip_display();
}

void draw_hud() {
      hud_graphics();
      for (int i = 0; i < lives; i++) {
            lives_graphics(70*i);
      }
}

void init_hud() {
      al_init_font_addon();
      font = al_create_builtin_font();
      text_color = al_map_rgb(0, 255, 255);
}
