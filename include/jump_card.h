#ifndef __jump_card_h
#define __jump_card_h
#include "card.h"
namespace MyUno
{
	class JumpCard : public Card {
	public:
		JumpCard(Color color);
		bool CanBePlayed();
		void ExecuteAction();
	};
}
#endif