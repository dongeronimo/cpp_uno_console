#include "jump_card.h"
#include "game_manager.h"
using namespace MyUno;
JumpCard::JumpCard(Color color)
	:Card(color, Jump)
{
}

bool MyUno::JumpCard::CanBePlayed(const Card* topDiscardPileCard) const
{
	//is there any card?
	bool isEmpty = topDiscardPileCard == nullptr;
	//Is a numeric card?
	bool isJumpCard = !isEmpty && dynamic_cast<const JumpCard*>(topDiscardPileCard) != nullptr;
	bool isSameColor = !isEmpty && topDiscardPileCard->color == this->color;
	return isJumpCard || isSameColor || isEmpty;
}

void MyUno::JumpCard::ExecuteAction()
{
	GameManager::GetInstance().Jump();
}
