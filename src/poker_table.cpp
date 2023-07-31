#include "poker_table.h"

#include "evaluate.h"
#include "poker_deck.h"
#include "poker_pocket.h"
#include "poker_dealer.h"
#include "poker_hand.h"

namespace Poker
{
    Table::Table(Deck _deck)
    {
        this->deck = _deck;
        this->state = State::PREFLOP;
    }

    void Table::deal_pockets()
    {
        for (int i = 0; i < 2; i++)
        {
            this->pockets.push_back(Pocket(this->deck.deal(), this->deck.deal()));
        }
    }

    void Table::deal_flop()
    {
        this->dealer = Dealer(this->deck.deal(), this->deck.deal(), this->deck.deal());
    }

    void Table::deal_turn()
    {
        this->dealer.deal_turn(this->deck.deal());
    }

    void Table::deal_river()
    {
        this->dealer.deal_river(this->deck.deal());
    }

    bn::vector<Pocket, 2> Table::get_pockets()
    {
        return this->pockets;
    }

    Pocket Table::get_pocket(int index)
    {
        return this->pockets[index];
    }

    Pocket Table::get_player_pocket()
    {
        return this->pockets[0];
    }

    Pocket Table::get_opponent_pocket()
    {
        return this->pockets[1];
    }

    Dealer Table::get_dealer()
    {
        return this->dealer;
    }

    Result Table::compete(Hand player, Hand opponent)
    {
        bn::vector<Card, 7> player_cards = player.getCards();
        bn::vector<Card, 7> opponent_cards = opponent.getCards();

        int player_res = evaluate_7cards(player_cards[0],
                                         player_cards[1],
                                         player_cards[2],
                                         player_cards[3],
                                         player_cards[4],
                                         player_cards[5],
                                         player_cards[6]);

        int opponent_res = evaluate_7cards(opponent_cards[0],
                                           opponent_cards[1],
                                           opponent_cards[2],
                                           opponent_cards[3],
                                           opponent_cards[4],
                                           opponent_cards[5],
                                           opponent_cards[6]);
        Result res;
        if (player_res > opponent_res)
            res.player_result = MatchResult::LOSE;
        else if (player_res == opponent_res)
            res.player_result = MatchResult::TIE;
        else
            res.player_result = MatchResult::WIN;

        return res;
    }
}