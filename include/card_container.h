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
		CardContainer() {}
		CardContainer(vector<shared_ptr<Card>> other);
		vector<shared_ptr<Card>> GetCards() const {
			return cards;
		}
		const shared_ptr<Card> Top() const;
		void Add(shared_ptr<Card> card);
		void Remove(shared_ptr<Card> which);
		shared_ptr<Card> BuyTopCard();
		const int Count() const;
	};
}
#endif