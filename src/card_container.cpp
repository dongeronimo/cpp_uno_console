#include "card_container.h"
#include "card.h"
#include <memory>
#include <vector>
#include "random.h"
#include <algorithm>
using namespace std;
using namespace MyUno;

MyUno::CardContainer::CardContainer(vector<shared_ptr<Card>> other)
{
    for (auto card : other)
        cards.push_back(card);
}

const shared_ptr<Card> MyUno::CardContainer::Top() const
{
    return cards.empty() ? nullptr : cards[Count() - 1];
}

void MyUno::CardContainer::Add(shared_ptr<Card> card)
{
    cards.push_back(card);
}

shared_ptr<Card> MyUno::CardContainer::BuyTopCard()
{
    auto topCard = Top();
    Remove(topCard);
    return topCard;
}

void MyUno::CardContainer::Shuffle()
{
    std::shuffle(cards.begin(), cards.end(), MyRandom::GetInstance().GetGenerator());
}

void MyUno::CardContainer::Remove(shared_ptr<Card> which)
{
    cards.erase(std::remove_if(
        cards.begin(),
        cards.end(),
        [which](std::shared_ptr<Card> card) {
            return card == which;
        }
    ));
}

const int MyUno::CardContainer::Count() const
{
    return cards.size();
}
