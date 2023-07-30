#include "bn_sprite_text_generator.h"
#include "bn_display.h"
#include "scene_type.h"
#include <bn_fixed.h>

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

constexpr bn::fixed text_y_inc = 14;
constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

scene_type menu_screen();

#endif // MENU_SCREEN_H