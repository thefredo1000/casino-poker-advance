#include <bn_random.h>
#include <bn_math.h>

#include "cards.h"


Hand::Hand(Pocket pocket, bn::vector<Card, 5> deal)
{
    this->cards->push_back(pocket.card1);
    this->cards->push_back(pocket.card2);
    for (int i = 0; i < 5; i++)
        this->cards->push_back(deal[i]);
}

Deck::Deck()
{
    this->deckSize = 52;
    for (size_t i = 0; i < 52; i++)
    {
        this->deck.push_back(Card(static_cast<Rank>(i % 13), static_cast<Suit>(i / 13)));
    }
}

void Deck::shuffle()
{
    for (int i = 0; i < 52; i++)
    {
        bn::random rng = bn::random();
        rng.update();
        int j = rng.get_int(i + 1);
        Card temp = this->deck[i];
        this->deck[i] = this->deck[j];
        this->deck[j] = temp;
    }
}

Card Deck::deal()
{
    Card dealtCard = this->deck[this->deckSize - 1];
    this->deckSize--;
    return dealtCard;
}

int Deck::get_deck_size()
{
    return this->deckSize;
}

void Deck::restart()
{
    this->deckSize = 52;
    this->deck.clear();
    for (size_t i = 0; i < 52; i++)
    {
        this->deck.push_back(Card(static_cast<Rank>(i % 13), static_cast<Suit>(i / 13)));
    }
}

Table::Table(Deck _deck)
{
    this->deck = _deck;
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

Result Table::compete(Hand player, Hand opponent) {
    
}
