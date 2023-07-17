#include "cards.h"
#include <bn_random.h>
#include <bn_math.h>

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
    for (size_t i = 0; i < 52; i++)
    {
        bn::random rng = bn::random();
        int j = rng.get_int(52);
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
