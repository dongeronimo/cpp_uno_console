#include "plus_2_card.h"
using namespace MyUno;

Plus2Card::Plus2Card(Color color)
	:Card(color, Plus2)
{
}

bool MyUno::Plus2Card::CanBePlayed(const Card* topDiscardPileCard) const
{
	//is there any card?
	bool isEmpty = topDiscardPileCard == nullptr;
	//Is a numeric card?
	bool isPlus2 = !isEmpty && dynamic_cast<const Plus2Card*>(topDiscardPileCard) != nullptr;
	bool isSameColor = !isEmpty && topDiscardPileCard->color == this->color;
	return isPlus2 || isSameColor || isEmpty;
}

void MyUno::Plus2Card::ExecuteAction()
{
}
