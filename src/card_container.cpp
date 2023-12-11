#include "card_container.h"
#include "card.h"
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;
using namespace MyUno;
shared_ptr<Card> MyUno::CardContainer::Top()
{
    return cards[Count() - 1];
}

void MyUno::CardContainer::Add(shared_ptr<Card> card)
{
    cards.push_back(card);
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

int MyUno::CardContainer::Count()
{
    return cards.size();
}
