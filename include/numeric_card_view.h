#pragma once
#include "card_view.h"
namespace MyUno
{
    class NumericCardView : public CardView
    {
    public:
        NumericCardView();
        virtual void Print(shared_ptr<Card> card) override;

    };
}