#ifndef __deck_generator_h
#define __deck_generator_h
#include "card.h"
#include "card_container.h"
namespace MyUno
{
	class DeckGenerator
	{
	public:
		CardContainer Generate();
	};
}
#endif