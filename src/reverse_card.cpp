#include "reverse_card.h"
using namespace MyUno;

ReverseCard::ReverseCard(Color color)
	:Card(color, Reverse)
{
}

bool MyUno::ReverseCard::CanBePlayed()
{
	return false;
}

void MyUno::ReverseCard::ExecuteAction()
{
}
