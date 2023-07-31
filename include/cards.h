#include <bn_vector.h>
#include <bn_random.h>
#include <bn_math.h>

#ifndef CARDS_H // include guard
#define CARDS_H

enum class suit
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
};

enum rank
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

// enum class for win, lose, tie
enum class player_result
{
    WIN,
    LOSE,
    TIE
};

enum class hand_rank
{
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

struct result
{
    player_result player_res;
    hand_rank player_hand_rank;
    hand_rank opponent_hand_rank;
};

class Card
{
public:
    Card(rank _rank, suit _suit) : rank(_rank), suit(_suit){};
    rank get_rank() const { return this->rank; }
    suit get_suit() const { return this->suit; }
    bn::string<8> to_string()
    {
        bn::string<8> str;
        switch (this->suit)
        {
        case suit::CLUBS:
            str = "C-";
            break;
        case suit::DIAMONDS:
            str = "D-";
            break;
        case suit::HEARTS:
            str = "H-";
            break;
        default:
            str = "S-";
            break;
        }
        str += bn::to_string<8>(static_cast<int>(this->rank) + 2);
        return str;
    }
    operator int() const
    {
        return static_cast<int>(this->rank) * 4 + static_cast<int>(this->suit);
    }

private:
    rank rank;
    suit suit;
};

class Deck
{
public:
    Deck();
    void shuffle();
    Card deal();
    int get_deck_size();
    void restart();
    bn::vector<Card, 52> get_deck() const
    {
        return this->deck;
    }
    void log_deck();

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
    bn::vector<Card, 7> getCards()
    {
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
    result compete(Hand player, Hand opponent);

private:
    Deck deck;
    Dealer dealer;
    bn::vector<Pocket, 2> pockets;
};

#endif /* MY_CLASS_H */
