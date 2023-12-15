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
