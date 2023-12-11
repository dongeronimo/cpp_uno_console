#ifndef __numeric_card_h
#define __numeric_card_h
#include "card.h"
namespace MyUno
{
	class NumericCard : public Card 
	{
	public:
		NumericCard(Color color, int number);
		bool CanBePlayed();
		void ExecuteAction();

	};

}
#endif