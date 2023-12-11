#ifndef __plus2_card_h
#define __plus2_card_h
#include "card.h"
namespace MyUno
{
	class Plus2Card : public Card 
	{
	public:
		Plus2Card(Color color);
		bool CanBePlayed();
		void ExecuteAction();
		virtual ~Plus2Card() {}
	};

}
#endif