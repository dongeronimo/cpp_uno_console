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
        CardContainer hand;
        const string name;
    public:
        Player(string name);
        void GiveCard(shared_ptr<Card> card);
        vector<shared_ptr<Card>> GetCards() {
            return hand.GetCards();
        }

    };
}
#endif
