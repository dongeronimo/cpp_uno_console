#include "reverse_card_view.h"

MyUno::ReverseCardView::ReverseCardView() :CardView({Reverse})
{
}

void MyUno::ReverseCardView::Draw(shared_ptr<Card> card)
{
    PrintCard(card);
}
