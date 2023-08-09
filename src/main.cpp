/*
 * Copyright (c) 2020-2023 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */
#include "bn_core.h"
#include "bn_sram.h"
#include "bn_music.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprites_mosaic_actions.h"

#include "bn_music_items.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_regular_bg_items_title_screen.h"
#include "bn_sprite_items_red_sprite.h"
#include "bn_sprite_items_chips.h"
#include "bn_sprite_items_chip_margin.h"
#include "bn_sprite_items_cards_diamond.h"
#include "bn_sprite_items_cards_hearts.h"
#include "bn_sprite_items_cards_spades.h"
#include "bn_sprite_items_cards_clubs.h"
#include "bn_sprite_items_card_back.h"

#include "poker_deck.h"
#include "poker_pocket.h"
#include "poker_dealer.h"
#include "poker_hand.h"
#include "poker_table.h"

#include "scene_type.h"
#include "title_screen.h"
#include "menu_screen.h"
#include "match_screen.h"
#include "extras_screen.h"
#include <bn_log.h>

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

    Game::SceneType scene = Game::SceneType::TITLE;

    while (1)
    {
        switch (scene)
        {
        case Game::SceneType::TITLE:
            Game::title_screen();
            scene = Game::SceneType::MENU;
            bn::music_items::hassans_spaceship.play(0.5);
            break;
        case Game::SceneType::MENU:
            scene = Game::menu_screen();
            BN_LOG("SceneType: ", int(scene));
            break;
        case Game::SceneType::GAME:
            scene = Game::match_screen(text_generator);
            break;
        case Game::SceneType::EXTRAS:
            scene = Game::extras_screen();
            break;
        default:
            break;
        }
    }
}
