#include "bn_sprite_text_generator.h"
#include "bn_display.h"

#ifndef MATCH_SCREEN_H
#define MATCH_SCREEN_H

constexpr bn::fixed text_y_inc = 14;
constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

void menu_screen_fake(bn::sprite_text_generator &text_generator);

#endif // MATCH_SCREEN_H