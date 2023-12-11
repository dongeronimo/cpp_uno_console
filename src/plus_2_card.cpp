#include "plus_2_card.h"
using namespace MyUno;

Plus2Card::Plus2Card(Color color)
	:Card(color, Plus2)
{
}

bool MyUno::Plus2Card::CanBePlayed()
{
	return false;
}

void MyUno::Plus2Card::ExecuteAction()
{
}
