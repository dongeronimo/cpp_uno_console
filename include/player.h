#ifndef __player_h
#define __player_h
#include <string>
#include <memory>
#include "card_container.h"
using namespace std;
namespace MyUno
{
    class Card;
    class Player
    {
    private:
        bool calledUno;
        CardContainer hand;
    public:
        Player(string name);
        const string name;
        void GiveCard(shared_ptr<Card> card);
        void RemoveCardFromHand(shared_ptr<Card> which);
        vector<shared_ptr<Card>> GetCards() {
            return hand.GetCards();
        }
        bool operator==(const Player& other)const {
            return name == other.name;
        }
        bool operator!=(const Player& other)const {
            return !(*this == other);
        }
        bool CanPlayAnyCard(const Card* topDiscardPile) const;
        bool HasPlus2()const;
        bool CanCallUno()const;
        void SetCalledUno(bool v) { calledUno = v; }
        bool CalledUno() { return calledUno; }
    };
}
#endif
