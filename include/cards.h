#include <bn_vector.h>
#include <bn_random.h>
#include <bn_math.h>

#ifndef CARDS_H // include guard
#define CARDS_H

enum Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};
enum Rank
{
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

struct Card
{
    Rank rank;
    Suit suit;
    // Constructor:
    Card(Rank _rank, Suit _suit) : rank(_rank), suit(_suit) {}
};

class Deck
{
public:
    Deck();
    void shuffle();
    Card deal();
    int get_deck_size();
    void restart();

private:
    bn::vector<Card, 52> deck;
    int deckSize;
};

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

struct Pocket
{
    Card card1;
    Card card2;
    bool playing = true;
    // Constructor
    Pocket(Card _card1, Card _card2) : card1(_card1), card2(_card2) {}
};

class Hand
{
    bn::vector<Card, 7> cards[7];
    Hand(Pocket pocket, bn::vector<Card, 5> deal);
};

Hand::Hand(Pocket pocket, bn::vector<Card, 5> deal)
{
    this->cards->push_back(pocket.card1);
    this->cards->push_back(pocket.card2);
    for (int i = 0; i < 5; i++)
        this->cards->push_back(deal[i]);
}

class Dealer
{
public:
    // Constructor
    Dealer() {}
    Dealer(Card card1, Card card2, Card card3)
    {
        this->cards.push_back(card1);
        this->cards.push_back(card2);
        this->cards.push_back(card3);
    }
    void deal_turn(Card card)
    {
        this->cards.push_back(card);
    }
    void deal_river(Card card)
    {
        this->cards.push_back(card);
    }
    bn::vector<Card, 5> get_cards()
    {
        return this->cards;
    }

private:
    bn::vector<Card, 5> cards;
};

// Poker table
class Table
{
public:
    Table();
    Table(Deck deck);
    void deal_pockets();
    void deal_flop();
    void deal_turn();
    void deal_river();
    bn::vector<Pocket, 2> get_pockets();
    Pocket get_pocket(int index);
    Pocket get_player_pocket();
    Pocket get_opponent_pocket();
    Dealer get_dealer();

private:
    Deck deck;
    Dealer dealer;
    bn::vector<Pocket, 2> pockets;
};

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

#endif /* MY_CLASS_H */
