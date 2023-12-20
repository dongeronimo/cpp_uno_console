#ifndef __reverse_card_h
#define __reverse_card_h
#include "card.h"
namespace MyUno
{
	class ReverseCard : public Card 
	{
	public:
		ReverseCard(Color color);
		bool CanBePlayed(const Card* topDiscardPileCard)  const;
		void ExecuteAction();
		virtual ~ReverseCard() {}
	};

}
#endif