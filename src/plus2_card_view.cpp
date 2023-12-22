#include "plus2_card_view.h"
#include "card_print.h"
MyUno::Plus2CardView::Plus2CardView()
    :CardView({Plus2})
{
}

void MyUno::Plus2CardView::Draw(shared_ptr<Card> card)
{
    PrintCard(card);
}
