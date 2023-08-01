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
    SceneType menu_screen()
    {

        bn::bg_palettes::set_transparent_color(bn::color(6, 12, 9));
        bn::sprite_text_generator title_text_generator(common::variable_16x16_sprite_font);
        bn::sprite_text_generator subtitle_text_generator(common::variable_8x8_sprite_font);
        title_text_generator.set_center_alignment();
        subtitle_text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;

        title_text_generator.generate(0, 40 - text_y_limit, "Play", text_sprites);
        title_text_generator.generate(0, 64 - text_y_limit, "Options", text_sprites);
        title_text_generator.generate(0, 88 - text_y_limit, "Extras", text_sprites);
        title_text_generator.generate(0, 112 - text_y_limit, "Credits", text_sprites);

        for (int i = 0; i < text_sprites.size(); i++)
        {
            text_sprites[i].set_scale(1, 2);
        }

        bn::sprite_ptr card_sprite_left = bn::sprite_items::cards_spades.create_sprite(-56, -24);
        bn::sprite_ptr card_sprite_right = bn::sprite_items::cards_diamond.create_sprite(56, -24);

        int text_index = 0;

        while (!bn::keypad::a_pressed() && !bn::keypad::start_pressed())
        {
            card_sprite_left.set_y((text_index - 1) * 24);
            card_sprite_right.set_y((text_index - 1) * 24);
            if (bn::keypad::up_pressed())
            {
                text_index = text_index - (text_index != 0);
            }
            else if (bn::keypad::down_pressed())
            {
                text_index = text_index + (text_index != 3);
            }

            bn::core::update();
        }

        return Game::SceneType(text_index + 2);
    }
}