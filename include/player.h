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
    public:
        Player(string name);
        const string name;
        void GiveCard(shared_ptr<Card> card);
        vector<shared_ptr<Card>> GetCards() {
            return hand.GetCards();
        }
        bool operator==(const Player& other)const {
            return name == other.name;
        }
        bool operator!=(const Player& other)const {
            return !(*this == other);
        }
    };
}
#endif
