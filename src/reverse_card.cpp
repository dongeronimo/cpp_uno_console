#include "reverse_card.h"
using namespace MyUno;

ReverseCard::ReverseCard(Color color)
	:Card(color, Reverse)
{
}

bool MyUno::ReverseCard::CanBePlayed(const Card* topDiscardPileCard) const
{
	//is there any card?
	bool isEmpty = topDiscardPileCard == nullptr;
	//Is a numeric card?
	bool isReverse = !isEmpty && dynamic_cast<const ReverseCard*>(topDiscardPileCard) != nullptr;
	bool isSameColor = !isEmpty && topDiscardPileCard->color == this->color;
	return isReverse || isSameColor || isEmpty;
}

void MyUno::ReverseCard::ExecuteAction()
{
}
