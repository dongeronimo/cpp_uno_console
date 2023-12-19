#pragma once
#include <memory>
#include <vector>
#include "card.h"
using namespace std;
namespace MyUno
{
    class Card;
    class CardView
    {
    private:
        const vector<Type> acceptableTypes;
    public:
        CardView(vector<Type> acceptableTypes);
        bool CanProcess(const Type& type);
        virtual void Print(shared_ptr<Card> card) = 0;
    };
}