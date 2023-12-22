#pragma once
#include "card_view.h"
#include "card_print.h"
namespace MyUno
{
    class ReverseCardView : public CardView
    {
    public:
        ReverseCardView();
        virtual void Draw(shared_ptr<Card> card) override;

    };
}