#ifndef __match_window_h
#define __match_window_h
#include "window.h"
#include <vector>
#include <memory>

using namespace std;
namespace MyUno
{
	enum Type;
	class Card;
	class CardView;
	class WindowSystem;
	class MatchWindow : public Window
	{
	private:
		vector<shared_ptr<CardView>> cardViewProcessors;
		shared_ptr<CardView> GetCardView(MyUno::Type type);
		shared_ptr<Card> ChooseCard(const vector<shared_ptr<Card>>& cardsInHand, const std::shared_ptr<Card>& topDiscardPile);
		int AskForCard(const vector<shared_ptr<Card>>& cardsInHand);
		bool IsThereAnyCardThatCanBePlayed(const vector<shared_ptr<Card>>& cardsInHand, const std::shared_ptr<Card>& topDiscardPile);
	public:
		MatchWindow(WindowSystem& manager);
		void Draw();
		virtual ~MatchWindow() {}
	};
}

#endif