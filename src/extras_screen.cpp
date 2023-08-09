#include "menu_screen.h"

#include "bn_bg_palettes.h"

#include "bn_core.h"
#include "scene_type.h"
#include "common_variable_8x8_sprite_font.h"
#include "common_variable_16x16_sprite_font.h"
#include "bn_sprite_items_cards_diamond.h"
#include "bn_sprite_items_cards_hearts.h"
#include "bn_sprite_items_cards_spades.h"
#include "bn_sprite_items_cards_clubs.h"
#include "bn_sprite_items_card_back.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_keypad.h"

namespace Game
{
    SceneType extras_screen()
    {
        // Background color
        bn::bg_palettes::set_transparent_color(bn::color(15, 10, 9));
        bn::sprite_text_generator title_text_generator(common::variable_16x16_sprite_font);
        title_text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 64> text_sprites;

        title_text_generator.generate(0, 8 - text_y_limit, "How to play:", text_sprites);

        // Scale the text
        for (int i = 0; i < text_sprites.size(); i++)
        {
            text_sprites[i].set_scale(1, 2);
        }

        bn::sprite_text_generator description_text_generator(common::variable_8x8_sprite_font);
        description_text_generator.set_center_alignment();
        description_text_generator.generate(0, -40, "- press A to play", text_sprites);
        description_text_generator.generate(0, -20, "- press A to call", text_sprites);
        description_text_generator.generate(0, 0, "- press B to fold", text_sprites);

        bool play = true;
        while (play)
        {

            if (bn::keypad::b_pressed())
                play = false;

            bn::core::update();
        }

        return Game::SceneType(1);
    }
}