#pragma once
#include "card_view.h"
#include "card_print.h"
namespace MyUno
{
    class JumpCardView : public CardView
    {
    public:
        JumpCardView();
        virtual void Draw(shared_ptr<Card> card) override;

    };
}