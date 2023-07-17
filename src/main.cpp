/*
 * Copyright (c) 2020-2023 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_music.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"

#include "bn_music_items.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_items_red_sprite.h"
#include "bn_sprite_items_cards_diamond.h"
#include "bn_sprite_items_cards_hearts.h"
#include "bn_sprite_items_cards_spades.h"
#include "bn_sprite_items_cards_clubs.h"

#include "cards.h"

namespace
{
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

    void title_screen(bn::sprite_text_generator &text_generator)
    {
        bn::music_items::hassans_spaceship.play(0.5);

        Deck deck = Deck();

        bn::random rng = bn::random();
        deck.shuffle(rng.get());

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
                deck.shuffle(rng.get());
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
            text_stream.append(" Gay poker ");
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

    title_screen(text_generator);
}
