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
    int getDeckSize();

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
        int j = rng.get() % (i + 1);
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

int Deck::getDeckSize()
{
    return this->deckSize;
}

struct Hand
{
    Card card1;
    Card card2;
    bool playing = true;
    // Constructor
    Hand(Card _card1, Card _card2) : card1(_card1), card2(_card2) {}
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
    void dealTurn(Card card)
    {
        this->cards.push_back(card);
    }
    void dealRiver(Card card)
    {
        this->cards.push_back(card);
    }
    bn::vector<Card, 5> getCards()
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
    void dealHands();
    void dealFlop();
    void dealTurn();
    void dealRiver();
    bn::vector<Hand, 2> getHands();
    Hand getHand(int index);
    Dealer getDealer();

private:
    Deck deck;
    Dealer dealer;
    bn::vector<Hand, 2> hands;
};

Table::Table(Deck _deck)
{
    this->deck = _deck;
}

void Table::dealHands()
{
    for (int i = 0; i < 1; i++)
    {
        this->hands.push_back(Hand(this->deck.deal(), this->deck.deal()));
    }
}

void Table::dealFlop()
{
    this->dealer = Dealer(this->deck.deal(), this->deck.deal(), this->deck.deal());
}

void Table::dealTurn()
{
    this->dealer.dealTurn(this->deck.deal());
}

void Table::dealRiver()
{
    this->dealer.dealRiver(this->deck.deal());
}

bn::vector<Hand, 2> Table::getHands()
{
    return this->hands;
}

Hand Table::getHand(int index)
{
    return this->hands[index];
}

Dealer Table::getDealer()
{
    return this->dealer;
}

#endif /* MY_CLASS_H */
