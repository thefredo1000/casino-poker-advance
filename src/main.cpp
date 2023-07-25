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
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprites_mosaic_actions.h"

#include "bn_music_items.h"

#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"
#include "common_variable_8x16_sprite_font.h"
#include "common_variable_16x16_sprite_font.h"
#include "bn_regular_bg_items_title_screen.h"
#include "bn_sprite_items_red_sprite.h"
#include "bn_sprite_items_chips.h"
#include "bn_sprite_items_chip_margin.h"
#include "bn_sprite_items_cards_diamond.h"
#include "bn_sprite_items_cards_hearts.h"
#include "bn_sprite_items_cards_spades.h"
#include "bn_sprite_items_cards_clubs.h"
#include "bn_sprite_items_card_back.h"

#include "cards.h"

namespace
{
    enum TableState
    {
        PREFLOP,
        FLOP,
        TURN,
        RIVER,
        SHOWDOWN
    };

    struct Position
    {
        bn::fixed x;
        bn::fixed y;
        Position(bn::fixed _x, bn::fixed _y) : x(_x), y(_y) {}
    };

    constexpr bn::fixed text_y_inc = 14;
    constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;
    const Position player_hand_position(0, 20);
    bn::fixed dealer_cards_x[5] = {-60, -30, 0, 30, 60};

    void title_screen()
    {

        bn::music_items::erotic.play(0.25);
        bn::regular_bg_ptr green_bg = bn::regular_bg_items::title_screen.create_bg(8, 48);

        bn::sprite_text_generator title_text_generator(common::variable_16x16_sprite_font);
        bn::sprite_text_generator subtitle_text_generator(common::variable_8x8_sprite_font);
        // bn::sprite_text_generator text_generator(fixed_32x64_sprite_font);
        title_text_generator.set_center_alignment();
        subtitle_text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;

        bn::sprite_ptr diamond_cards_sprite = bn::sprite_items::cards_diamond.create_sprite(-64, 40);
        bn::sprite_ptr hearts_cards_sprite = bn::sprite_items::cards_hearts.create_sprite(24, 50);
        bn::sprite_ptr spades_cards_sprite = bn::sprite_items::cards_spades.create_sprite(-24, 50);
        bn::sprite_ptr clubs_cards_sprite = bn::sprite_items::cards_clubs.create_sprite(64, 40);

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

        int rotation = 0;
        bool clockwise = true;
        while (!bn::keypad::any_pressed())
        {

            diamond_cards_sprite.set_rotation_angle(rotation);
            hearts_cards_sprite.set_rotation_angle(rotation);
            spades_cards_sprite.set_rotation_angle(rotation);
            clubs_cards_sprite.set_rotation_angle(rotation);

            if (clockwise)
            {
                rotation++;
            }
            else
            {
                rotation--;
            }

            if (rotation > 20 && rotation < 340)
            {
                clockwise = !clockwise;
            }
            else if (rotation == 0)
            {
                rotation = 360;
            }
            else if (rotation == 360)
            {
                rotation = 0;
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

    uint32_t menu_screen()
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

        bn::music::stop();
        return text_index;
    }

    void show_card(Card &card, bn::sprite_ptr &hand_sprite)
    {
        while(hand_sprite.vertical_scale() > 0.1)
        {
            hand_sprite.set_vertical_scale(hand_sprite.vertical_scale() - 0.1);
            bn::core::update();
        }

        switch (card.suit)
        {
        case DIAMONDS:
            hand_sprite = bn::sprite_items::cards_diamond.create_sprite(hand_sprite.x(), hand_sprite.y());
            hand_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(card.rank));
            break;
        case HEARTS:
            hand_sprite = bn::sprite_items::cards_hearts.create_sprite(hand_sprite.x(), hand_sprite.y());
            hand_sprite.set_tiles(bn::sprite_items::cards_hearts.tiles_item().create_tiles(card.rank));
            break;
        case SPADES:
            hand_sprite = bn::sprite_items::cards_spades.create_sprite(hand_sprite.x(), hand_sprite.y());
            hand_sprite.set_tiles(bn::sprite_items::cards_spades.tiles_item().create_tiles(card.rank));
            break;
        case CLUBS:
            hand_sprite = bn::sprite_items::cards_clubs.create_sprite(hand_sprite.x(), hand_sprite.y());
            hand_sprite.set_tiles(bn::sprite_items::cards_clubs.tiles_item().create_tiles(card.rank));
            break;
        default:
            hand_sprite = bn::sprite_items::card_back.create_sprite(hand_sprite.x(), hand_sprite.y());
            break;
        }

        while(hand_sprite.vertical_scale() <= 1)
        {
            hand_sprite.set_vertical_scale(hand_sprite.vertical_scale() + 0.1);
            bn::core::update();
        }

    }

    void move_card(bn::sprite_ptr &card_sprite, bn::fixed x_destination, bn::fixed y_destination)
    {
        const int movement_speed = 2; // You can adjust the speed as needed

        bn::fixed x = card_sprite.x();
        bn::fixed y = card_sprite.y();

        while (card_sprite.x() != x_destination || card_sprite.y() != y_destination)
        {
            if (card_sprite.x() != x_destination)
            {
                if (x < x_destination)
                {
                    x += movement_speed;
                    if (x > x_destination)
                        x = x_destination; // Clamp to destination if overshooting
                }
                else
                {
                    x -= movement_speed;
                    if (x < x_destination)
                        x = x_destination; // Clamp to destination if overshooting
                }
            }

            if (card_sprite.y() != y_destination)
            {
                if (y < y_destination)
                {
                    y += movement_speed;
                    if (y > y_destination)
                        y = y_destination; // Clamp to destination if overshooting
                }
                else
                {
                    y -= movement_speed;
                    if (y < y_destination)
                        y = y_destination; // Clamp to destination if overshooting
                }
            }

            card_sprite.set_x(x);
            card_sprite.set_y(y);
            bn::core::update();
        }
    }

    void deck_screen(bn::sprite_text_generator &text_generator)
    {
        // Play music
        bn::music_items::hassans_spaceship.play(0.5);

        bn::vector<bn::sprite_ptr, 4> text_sprites;
        bn::string<32> text;
        bn::ostringstream text_stream(text);
        text_stream.append("Press A to play");
        text_generator.generate(-50, -70, text, text_sprites);

        // First Deck
        Deck deck = Deck();
        deck.shuffle();

        // First Table
        Table table = Table(deck);
        table.deal_hands();

        Hand player_hand = table.get_player_hand();
        Hand opponent_hand = table.get_opponent_hand();
        // Sprites
        bn::sprite_ptr deck_sprite = bn::sprite_items::card_back.create_sprite(80, -40);

        bn::vector<bn::sprite_ptr, 2> player_hand_sprite;
        player_hand_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));
        player_hand_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));

        bn::vector<bn::sprite_ptr, 2> opponent_hand_sprite;
        opponent_hand_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));
        opponent_hand_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));

        bn::vector<bn::sprite_ptr, 5> dealer_cards_sprite;
        dealer_cards_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));
        dealer_cards_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));
        dealer_cards_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));
        dealer_cards_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));
        dealer_cards_sprite.push_back(bn::sprite_items::card_back.create_sprite(80, -40));

        bn::sprite_ptr chip_margin = bn::sprite_items::chip_margin.create_sprite(0, 50);
        chip_margin.set_z_order(1);

        TableState table_state = PREFLOP;
        while (1)
        {

            if (table_state == PREFLOP)
                deck.shuffle();

            if (bn::keypad::start_pressed())
            {
                deck.shuffle();
                table = Table(deck);
                table.deal_hands();
                player_hand = table.get_player_hand();
                opponent_hand = table.get_opponent_hand();
                show_card(player_hand.card1, player_hand_sprite[0]);
                show_card(player_hand.card2, player_hand_sprite[1]);
            }

            // Animate the deal
            if (bn::keypad::a_pressed() && table_state == PREFLOP)
            {
                deck.shuffle();
                table = Table(deck);
                table.deal_hands();
                player_hand = table.get_player_hand();
                opponent_hand = table.get_opponent_hand();

                // Deal hands
                move_card(player_hand_sprite[0], (player_hand_position.x - 10), player_hand_position.y);
                show_card(player_hand.card1, player_hand_sprite[0]);
                move_card(opponent_hand_sprite[0], (player_hand_position.x - 10), -player_hand_position.y);
                move_card(player_hand_sprite[1], (player_hand_position.x + 10), player_hand_position.y);
                show_card(player_hand.card2, player_hand_sprite[1]);
                move_card(opponent_hand_sprite[1], (player_hand_position.x + 10), -player_hand_position.y);
                table_state = FLOP;
            }
            if (bn::keypad::a_pressed() && table_state == FLOP)
            {
                table.deal_flop();
                Dealer dealer = table.get_dealer();

                for (int i = 0; i < 3; i++)
                {
                    move_card(dealer_cards_sprite[i], dealer_cards_x[i], 0);
                    show_card(dealer.get_cards()[i], dealer_cards_sprite[i]);
                }
                table_state = TURN;
            }

            if (bn::keypad::a_pressed() && table_state == TURN)
            {
                table.deal_turn();
                Dealer dealer = table.get_dealer();
                move_card(dealer_cards_sprite[3], dealer_cards_x[3], 0);
                show_card(dealer.get_cards()[3], dealer_cards_sprite[3]);
                table_state = RIVER;
            }

            if (bn::keypad::a_pressed() && table_state == RIVER)
            {
                table.deal_river();
                Dealer dealer = table.get_dealer();
                move_card(dealer_cards_sprite[4], dealer_cards_x[4], 0);
                show_card(dealer.get_cards()[4], dealer_cards_sprite[4]);
                table_state = SHOWDOWN;
            }

            if (bn::keypad::a_pressed() && table_state == SHOWDOWN)
            {

                show_card(opponent_hand.card1, opponent_hand_sprite[0]);
                show_card(opponent_hand.card2, opponent_hand_sprite[1]);
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

    uint32_t option = menu_screen();
    bn::core::update();

    switch (option)
    {
    case 0:
        deck_screen(text_generator);
        break;
    default:
        break;
    }
}
