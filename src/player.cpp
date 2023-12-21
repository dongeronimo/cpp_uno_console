#include "player.h"
#include "card.h"
MyUno::Player::Player(string name)
    :name(name)
{
}

void MyUno::Player::GiveCard(shared_ptr<Card> card)
{
    hand.Add(card);
}

void MyUno::Player::RemoveCardFromHand(shared_ptr<Card> which)
{
    hand.Remove(which);
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
