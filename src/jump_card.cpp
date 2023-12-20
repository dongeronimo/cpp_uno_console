#include "jump_card.h"
using namespace MyUno;
JumpCard::JumpCard(Color color)
	:Card(color, Jump)
{
}

bool MyUno::JumpCard::CanBePlayed(const Card* topDiscardPileCard) const
{
	return false;
}

void MyUno::JumpCard::ExecuteAction()
{
}
