#pragma once
#include "card_view.h"
namespace MyUno
{
    class NumericCardView : public CardView
    {
    public:
        NumericCardView();
        virtual void Draw(shared_ptr<Card> card) override;

    };
}