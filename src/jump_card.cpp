#include "jump_card.h"
using namespace MyUno;
JumpCard::JumpCard(Color color)
	:Card(color, Jump)
{
}

bool MyUno::JumpCard::CanBePlayed()
{
	return false;
}

void MyUno::JumpCard::ExecuteAction()
{
}
