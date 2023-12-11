#ifndef __card_container_h
#define __card_container_h
#include "card.h"
#include <memory>
#include <vector>
using namespace std;
namespace MyUno
{
	class CardContainer 
	{
	private:
		vector<shared_ptr<Card>> cards;
	public:
		shared_ptr<Card> Top();
		void Add(shared_ptr<Card> card);
		void Remove(shared_ptr<Card> which);
		int Count();
	};
}
#endif