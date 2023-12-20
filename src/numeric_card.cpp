#include "numeric_card.h"
#include "card.h"
#include <exception>
#include <stdexcept>
using namespace MyUno;

Type NumberToType(unsigned int n) {
	switch (n)
	{
	case 0:
		return Zero;
	case 1:
		return One;
	case 2:
		return Two;
	case 3:
		return Three;
	case 4:
		return Four;
	case 5:
		return Five;
	case 6:
		return Six;
	case 7:
		return Seven;
	case 8:
		return Eight;
	case 9:
		return Nine;
	default:
		throw std::range_error("must be between 0 and 9");
	}
	
}

NumericCard::NumericCard(Color color, int number)
	:Card(color, NumberToType(number))
{
}
/// <summary>
/// Can only be played if the top discard pile card is the same color or the same type
/// </summary>
/// <param name="topDiscardPileCard"></param>
/// <returns></returns>
bool MyUno::NumericCard::CanBePlayed(const Card* topDiscardPileCard) const
{
	//is there any card?
	bool isEmpty = topDiscardPileCard == nullptr;
	//Is a numeric card?
	bool isNumeric = !isEmpty && dynamic_cast<const NumericCard*>(topDiscardPileCard) != nullptr;
	bool isSameColor = !isEmpty && topDiscardPileCard->color == this->color;
	return isNumeric || isSameColor || isEmpty;
}

void MyUno::NumericCard::ExecuteAction()
{
}
