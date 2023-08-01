#include "match_screen.h"

#include "bn_core.h"
#include "bn_sram.h"
#include "bn_music.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_display.h"

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

#include "poker_deck.h"
#include "poker_pocket.h"
#include "poker_dealer.h"
#include "poker_hand.h"
#include "poker_table.h"
#include "sram.h"

namespace Game
{

    void show_card(Poker::Card &card, bn::sprite_ptr &card_sprite)
    {
        while (card_sprite.vertical_scale() > 0.1)
        {
            card_sprite.set_vertical_scale(card_sprite.vertical_scale() - 0.1);
            bn::core::update();
        }

        switch (card.get_suit())
        {
        case Poker::Suit::DIAMONDS:
            card_sprite = bn::sprite_items::cards_diamond.create_sprite(card_sprite.x(), card_sprite.y());
            card_sprite.set_tiles(bn::sprite_items::cards_diamond.tiles_item().create_tiles(static_cast<int>(card.get_rank())));
            break;
        case Poker::Suit::HEARTS:
            card_sprite = bn::sprite_items::cards_hearts.create_sprite(card_sprite.x(), card_sprite.y());
            card_sprite.set_tiles(bn::sprite_items::cards_hearts.tiles_item().create_tiles(static_cast<int>(card.get_rank())));
            break;
        case Poker::Suit::SPADES:
            card_sprite = bn::sprite_items::cards_spades.create_sprite(card_sprite.x(), card_sprite.y());
            card_sprite.set_tiles(bn::sprite_items::cards_spades.tiles_item().create_tiles(static_cast<int>(card.get_rank())));
            break;
        case Poker::Suit::CLUBS:
            card_sprite = bn::sprite_items::cards_clubs.create_sprite(card_sprite.x(), card_sprite.y());
            card_sprite.set_tiles(bn::sprite_items::cards_clubs.tiles_item().create_tiles(static_cast<int>(card.get_rank())));
            break;
        default:
            card_sprite = bn::sprite_items::card_back.create_sprite(card_sprite.x(), card_sprite.y());
            break;
        }

        while (card_sprite.vertical_scale() <= 1)
        {
            card_sprite.set_vertical_scale(card_sprite.vertical_scale() + 0.1);
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

    void match_screen(bn::sprite_text_generator &text_generator)
    {
        // Play music
        bn::music_items::hassans_spaceship.play(0.5);

        // Money
        int money = read_sram();

        bn::vector<bn::sprite_ptr, 64> text_sprites;
        bn::string<32> text;
        bn::ostringstream text_stream(text);
        text_stream.append("Press A to play");
        text_generator.generate(-50, -70, text, text_sprites);
        text_generator.generate(-114, 70, "Money: ", text_sprites);
        text_generator.generate(-72, 70, bn::to_string<32>(money), text_sprites);

        // First Deck
        Poker::Deck deck = Poker::Deck();
        deck.shuffle();

        // First Table
        Poker::Table table = Poker::Table(deck);
        table.deal_pockets();

        Poker::Pocket player_pocket = table.get_player_pocket();
        Poker::Pocket opponent_pocket = table.get_opponent_pocket();

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

        bn::sprite_ptr ante_margin_sprite = bn::sprite_items::chip_margin.create_sprite(-18, 50);
        ante_margin_sprite.set_z_order(1);
        text_generator.generate(-32, 70, "ante", text_sprites);

        bn::sprite_ptr call_margin_sprite = bn::sprite_items::chip_margin.create_sprite(18, 50);
        call_margin_sprite.set_z_order(1);
        text_generator.generate(8, 70, "call", text_sprites);

        bn::sprite_ptr ante_chip_sprite = bn::sprite_items::chips.create_sprite(-18, 47);
        ante_chip_sprite.set_visible(false);

        bn::sprite_ptr call_chip_sprite = bn::sprite_items::chips.create_sprite(18, 47);
        call_chip_sprite.set_visible(false);

        bn::sprite_ptr bet_chip_sprite = bn::sprite_items::chips.create_sprite(-40, 47);
        int bet_chip_index = 0;

        int bet_amount = 1;

        for (int i = 0; i < 10; i++)
            bn::core::update();

        while (1)
        {

            if (bn::keypad::b_pressed())
            {
                write_sram(200);
            }

            if (bn::keypad::r_pressed())
            {
                write_sram(0);
            }

            if (table.get_state() == Poker::Table::State::PREFLOP)
            {
                deck.shuffle();
                deck.log_deck();
            }
            if (bn::keypad::up_pressed() && bet_amount < 32 && (bet_amount * 4) < money && (table.get_state() == Poker::Table::State::PREFLOP))
            {
                bet_amount *= 2;
                bet_chip_index++;
                bet_chip_sprite.set_tiles(bn::sprite_items::chips.tiles_item().create_tiles(bet_chip_index));
            }
            else if (bn::keypad::down_pressed() && bet_amount > 1 && table.get_state() == Poker::Table::State::PREFLOP)
            {
                bet_amount /= 2;
                bet_chip_index--;
                bet_chip_sprite.set_tiles(bn::sprite_items::chips.tiles_item().create_tiles(bet_chip_index));
            }

            // Animate the deal
            if (bn::keypad::a_pressed() && table.get_state() == Poker::Table::State::PREFLOP && money)
            {
                money -= bet_amount;
                ante_chip_sprite.set_tiles(bn::sprite_items::chips.tiles_item().create_tiles(bet_chip_index));
                ante_chip_sprite.set_visible(true);
                table = Poker::Table(deck);
                table.deal_pockets();
                player_pocket = table.get_player_pocket();
                opponent_pocket = table.get_opponent_pocket();

                // Deal hands
                move_card(player_hand_sprite[0], (player_hand_position.x - 10), player_hand_position.y);
                show_card(player_pocket.card1, player_hand_sprite[0]);

                move_card(opponent_hand_sprite[0], (player_hand_position.x - 10), -player_hand_position.y);

                move_card(player_hand_sprite[1], (player_hand_position.x + 10), player_hand_position.y);
                show_card(player_pocket.card2, player_hand_sprite[1]);

                move_card(opponent_hand_sprite[1], (player_hand_position.x + 10), -player_hand_position.y);
                table.set_state(Poker::Table::State::FLOP);
            }

            if (bn::keypad::a_pressed() && table.get_state() == Poker::Table::State::FLOP && money)
            {
                table.deal_flop();
                Poker::Dealer dealer = table.get_dealer();

                for (int i = 0; i < 3; i++)
                {
                    move_card(dealer_cards_sprite[i], dealer_cards_x[i], 0);
                    show_card(dealer.get_cards()[i], dealer_cards_sprite[i]);
                }
                table.set_state(Poker::Table::State::TURN);
            }

            if (bn::keypad::a_pressed() && table.get_state() == Poker::Table::State::TURN && money)
            {
                money -= bet_amount;
                call_chip_sprite.set_tiles(bn::sprite_items::chips.tiles_item().create_tiles(bet_chip_index));
                call_chip_sprite.set_visible(true);
                table.deal_turn();
                Poker::Dealer dealer = table.get_dealer();
                move_card(dealer_cards_sprite[3], dealer_cards_x[3], 0);
                show_card(dealer.get_cards()[3], dealer_cards_sprite[3]);

                table.set_state(Poker::Table::State::RIVER);

                table.deal_river();
                dealer = table.get_dealer();
                move_card(dealer_cards_sprite[4], dealer_cards_x[4], 0);
                show_card(dealer.get_cards()[4], dealer_cards_sprite[4]);
                table.set_state(Poker::Table::State::SHOWDOWN);
            }

            if (bn::keypad::a_pressed() && table.get_state() == Poker::Table::State::SHOWDOWN)
            {
                show_card(opponent_pocket.card1, opponent_hand_sprite[0]);
                show_card(opponent_pocket.card2, opponent_hand_sprite[1]);

                Poker::Dealer dealer = table.get_dealer();
                Poker::Hand player_hand(player_pocket, dealer.get_cards());
                Poker::Hand opponent_hand(opponent_pocket, dealer.get_cards());
                Poker::Result res = table.compete(player_hand, opponent_hand);
                switch (res.player_result)
                {
                case (Poker::MatchResult::WIN):
                    text_generator.generate(80, 70, "u won!", text_sprites);
                    money += bet_amount * 4;
                    write_sram(money);
                    break;
                case (Poker::MatchResult::LOSE):
                    text_generator.generate(80, 70, "u LOST", text_sprites);
                    write_sram(money);
                    break;
                default:
                    text_generator.generate(80, 70, "TIE", text_sprites);
                    break;
                }

                table.set_state(Poker::Table::State::END);
            }
            if (bn::keypad::a_pressed() && table.get_state() == Poker::Table::State::END)
            {
                break;
            }
            bn::core::update();
        }
    }
}