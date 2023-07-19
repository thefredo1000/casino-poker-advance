/*
 * Copyright (c) 2020-2023 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_music.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprites_mosaic_actions.h"

#include "bn_music_items.h"

#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"
#include "common_variable_8x16_sprite_font.h"
#include "common_variable_16x16_sprite_font.h"
#include "bn_sprite_items_red_sprite.h"
#include "bn_sprite_items_cards_diamond.h"
#include "bn_sprite_items_cards_hearts.h"
#include "bn_sprite_items_cards_spades.h"
#include "bn_sprite_items_cards_clubs.h"

#include "cards.h"

namespace
{
    constexpr bn::fixed text_y_inc = 14;
    constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    void show_player_hand(Hand hand)
    {

        if (hand.card1.suit == DIAMONDS)
        {

            bn::sprite_ptr diamond_cards_sprite = bn::sprite_items::cards_diamond.create_sprite(0, 0);
            diamond_cards_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(hand.card1.rank));
        }
        else
        {

            bn::sprite_ptr hearts_cards_sprite = bn::sprite_items::cards_hearts.create_sprite(0, 0);
            hearts_cards_sprite.set_tiles(bn::sprite_items::cards_hearts.tiles_item().create_tiles(hand.card1.rank));
        }
    }

    void title_screen()
    {

        bn::music_items::erotic.play(0.25);
        bn::sprite_text_generator title_text_generator(common::variable_16x16_sprite_font);
        bn::sprite_text_generator subtitle_text_generator(common::variable_8x8_sprite_font);
        // bn::sprite_text_generator text_generator(fixed_32x64_sprite_font);
        title_text_generator.set_center_alignment();
        subtitle_text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;

        title_text_generator.generate(0, 35 - text_y_limit, "CASINO HOLD 'EM", text_sprites);

        for (int i = 0; i < 7; i++)
        {
            text_sprites[i].set_scale(1, 2);
        }

        subtitle_text_generator.generate(0, 50 - text_y_limit, "advance", text_sprites);

        subtitle_text_generator.generate(0, text_y_limit, "RODRIGO CASALE 2023", text_sprites);

        bn::sprite_ptr diamond_cards_sprite = bn::sprite_items::cards_diamond.create_sprite(-42, 0);
        bn::sprite_ptr hearts_cards_sprite = bn::sprite_items::cards_hearts.create_sprite(16, 10);
        bn::sprite_ptr spades_cards_sprite = bn::sprite_items::cards_spades.create_sprite(-16, 10);
        bn::sprite_ptr clubs_cards_sprite = bn::sprite_items::cards_clubs.create_sprite(42, 0);

        diamond_cards_sprite.set_scale(1.4, 2);
        hearts_cards_sprite.set_scale(1.4, 2);
        spades_cards_sprite.set_scale(1.4, 2);
        clubs_cards_sprite.set_scale(1.4, 2);

        diamond_cards_sprite.set_mosaic_enabled(true);
        hearts_cards_sprite.set_mosaic_enabled(true);
        spades_cards_sprite.set_mosaic_enabled(true);
        clubs_cards_sprite.set_mosaic_enabled(true);
        for (int i = 0; i < text_sprites.size(); i++)
        {
            text_sprites[i].set_mosaic_enabled(true);
        }

        int i = 0;
        int slow = 0;
        bool clockwise = true;
        while (!bn::keypad::start_pressed())
        {

            diamond_cards_sprite.set_rotation_angle(i);
            hearts_cards_sprite.set_rotation_angle(i);
            spades_cards_sprite.set_rotation_angle(i);
            clubs_cards_sprite.set_rotation_angle(i);

            if (clockwise)
            {
                i++;
            }
            else
            {
                i--;
            }

            if (i > 20 && i < 340)
            {
                clockwise = !clockwise;
            }
            else if (i == 0)
            {
                i = 360;
            }
            else if (i == 360)
            {
                i = 0;
            }
            bn::core::update();
        }

        bn::sprites_mosaic_stretch_loop_action action(120, 1);
        for (unsigned int i = 0; i < 100; ++i)
        {
            action.update();
            bn::core::update();
        }
    }

    void menu_screen()
    {

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


        unsigned int text_index = 0;

        while (!bn::keypad::a_pressed() || !bn::keypad::start_pressed()
        {
            card_sprite_left.set_y((text_index - 1) * 24);
            card_sprite_right.set_y((text_index - 1) * 24);
            if(bn::keypad::up_pressed()) {
                text_index = text_index - (text_index != 0);
            } else if (bn::keypad::down_pressed()) {
                text_index = text_index + (text_index != 3);
            }

            bn::core::update();
        }

        bn::music::stop();
    }

    void deck_screen(bn::sprite_text_generator &text_generator)
    {
        bn::music_items::hassans_spaceship.play(0.5);

        Deck deck = Deck();

        bn::random rng = bn::random();
        deck.shuffle();

        Table table = Table(deck);

        table.dealHands();

        Hand hand = table.getHand(0);

        bn::sprite_ptr cards_sprite = bn::sprite_items::cards_diamond.create_sprite(1, 1);

        bn::sprite_ptr hand_sprite_1 = bn::sprite_items::cards_diamond.create_sprite(1, 1);
        bn::sprite_ptr hand_sprite_2 = bn::sprite_items::cards_diamond.create_sprite(1, 1);

        while (1)
        {
            if (bn::keypad::start_pressed())
            {
                deck.shuffle();
                table = Table(deck);
                table.dealHands();
                hand = table.getHand(0);
            }
            if (hand.card1.suit == DIAMONDS)
            {

                hand_sprite_1 = bn::sprite_items::cards_diamond.create_sprite(20, 20);
                hand_sprite_1.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(hand.card1.rank));
            }
            else if (hand.card1.suit == HEARTS)
            {

                hand_sprite_1 = bn::sprite_items::cards_hearts.create_sprite(20, 20);
                hand_sprite_1.set_tiles(bn::sprite_items::cards_hearts.tiles_item().create_tiles(hand.card1.rank));
            }
            else if (hand.card1.suit == SPADES)
            {

                hand_sprite_1 = bn::sprite_items::cards_spades.create_sprite(20, 20);
                hand_sprite_1.set_tiles(bn::sprite_items::cards_spades.tiles_item().create_tiles(hand.card1.rank));
            }
            else
            {

                hand_sprite_1 = bn::sprite_items::cards_clubs.create_sprite(20, 20);
                hand_sprite_1.set_tiles(bn::sprite_items::cards_clubs.tiles_item().create_tiles(hand.card1.rank));
            }

            if (hand.card2.suit == DIAMONDS)
            {

                hand_sprite_2 = bn::sprite_items::cards_diamond.create_sprite(40, 20);
                hand_sprite_2.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(hand.card2.rank));
            }
            else if (hand.card2.suit == HEARTS)
            {

                hand_sprite_2 = bn::sprite_items::cards_hearts.create_sprite(40, 20);
                hand_sprite_2.set_tiles(bn::sprite_items::cards_hearts.tiles_item().create_tiles(hand.card2.rank));
            }
            else if (hand.card2.suit == SPADES)
            {

                hand_sprite_2 = bn::sprite_items::cards_spades.create_sprite(40, 20);
                hand_sprite_2.set_tiles(bn::sprite_items::cards_spades.tiles_item().create_tiles(hand.card2.rank));
            }
            else
            {

                hand_sprite_2 = bn::sprite_items::cards_clubs.create_sprite(40, 20);
                hand_sprite_2.set_tiles(bn::sprite_items::cards_clubs.tiles_item().create_tiles(hand.card2.rank));
            }
            bn::vector<bn::sprite_ptr, 4> text_sprites;
            bn::string<32> text;
            bn::ostringstream text_stream(text);
            text_stream.append(hand.card1.rank + 1);
            text_stream.append(hand.card1.suit);
            text_stream.append(" & ");
            text_stream.append(hand.card2.rank + 1);
            text_stream.append(hand.card2.suit);
            text_stream.append("sexy poker");
            text_sprites.clear();
            text_generator.generate(-50, -50, text, text_sprites);

            if (bn::keypad::left_held())
            {
                cards_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(8));
                cards_sprite.set_x(cards_sprite.x() - 1);
            }
            else if (bn::keypad::right_held())
            {
                cards_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(12));
                cards_sprite.set_x(cards_sprite.x() + 1);
            }

            if (bn::keypad::up_held())
            {
                cards_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(4));
                cards_sprite.set_y(cards_sprite.y() - 1);
            }
            else if (bn::keypad::down_held())
            {
                cards_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(0));
                cards_sprite.set_y(cards_sprite.y() + 1);
            }
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    bn::bg_palettes::set_transparent_color(bn::color(6, 12, 9));

    title_screen();
    bn::core::update();
    bn::bg_palettes::set_transparent_color(bn::color(6, 12, 9));

    menu_screen();
    bn::core::update();
    deck_screen(text_generator);
}
