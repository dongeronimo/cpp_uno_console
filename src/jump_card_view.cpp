#include "jump_card_view.h"
#include "card_print.h"
MyUno::JumpCardView::JumpCardView()
    :CardView({Jump})
{
}

void MyUno::JumpCardView::Draw(shared_ptr<Card> card)
{
    PrintCard(card);
}
