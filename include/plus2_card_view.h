#pragma once
#include "card_view.h"
#include "card_print.h"
namespace MyUno
{
    class Plus2CardView : public CardView
    {
    public:
        Plus2CardView();
        virtual void Draw(shared_ptr<Card> card) override;

    };
}