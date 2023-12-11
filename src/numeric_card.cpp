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

bool MyUno::NumericCard::CanBePlayed()
{
	return false;
}

void MyUno::NumericCard::ExecuteAction()
{
}
