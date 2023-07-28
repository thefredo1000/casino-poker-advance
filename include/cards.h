#include <bn_vector.h>
#include <bn_random.h>
#include <bn_math.h>

#ifndef CARDS_H // include guard
#define CARDS_H

enum class Suit
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
};

enum Rank
{
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
    KING,
    ACE,
};

enum class Result
{
    WIN,
    LOSE,
    TIE
};

class Card
{
public:
    Card(Rank _rank, Suit _suit) : rank(_rank), suit(_suit){};
    Rank getRank() const { return this->rank; }
    Suit getSuit() const { return this->suit; }
    operator int() const
    {
        return static_cast<int>(this->rank) * 4 + static_cast<int>(this->suit);
    }

private:
    Rank rank;
    Suit suit;
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
public:
    Hand(Pocket pocket, bn::vector<Card, 5> deal);
    bn::vector<Card, 7> getCards() {
        return this->cards;
    }
private:
    bn::vector<Card, 7> cards;
};

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
    bn::vector<Card, 5> get_cards() const
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
    Result compete(Hand player, Hand opponent);

private:
    Deck deck;
    Dealer dealer;
    bn::vector<Pocket, 2> pockets;
};

#endif /* MY_CLASS_H */
