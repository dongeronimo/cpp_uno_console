#pragma once
#include "card_view.h"
#include "card_print.h"
namespace MyUno
{
    class NumericCardView : public CardView
    {
    public:
        NumericCardView();
        virtual void Draw(shared_ptr<Card> card) override;

    };
}