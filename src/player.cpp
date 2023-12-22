#include "player.h"
#include "card.h"
using namespace MyUno;
MyUno::Player::Player(string name)
    :name(name)
{
}

void MyUno::Player::GiveCard(shared_ptr<Card> card)
{
    hand.Add(card);
}

void MyUno::Player::RemoveCardFromHand(shared_ptr<Card> whichCard)
{
    hand.Remove(whichCard);
}

bool MyUno::Player::CanPlayAnyCard(const Card* topDiscardPile) const
{
    bool canPlay = false;
    auto cards = hand.GetCards();
    for (auto cardsIt = cards.begin(); cardsIt != cards.end(); ++cardsIt)
    {
        auto currentCard = *cardsIt;
        if (currentCard->CanBePlayed(topDiscardPile) == true)
            canPlay = true;
    }

    return canPlay;
}

bool Player::HasPlus2() const
{
    bool hasPlus2 = false;
    auto cards = hand.GetCards();
    for (auto cardsIt = cards.begin(); cardsIt != cards.end(); ++cardsIt)
    {
        auto currentCard = *cardsIt;
        if (currentCard->type == Plus2) 
        {
            hasPlus2 = true;
        }
    }
    return hasPlus2;
}
