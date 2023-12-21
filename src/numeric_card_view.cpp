#include "numeric_card_view.h"
#include "card_print.h"
using namespace MyUno;
std::vector<Type> numericTypes = { Type::Zero, Type::One, Type::Two, Type::Three,
    Type::Four, Type::Five, Type::Six, Type::Seven, Type::Eight, Type::Nine};

MyUno::NumericCardView::NumericCardView()
    :CardView(numericTypes)
{
}

void MyUno::NumericCardView::Draw(shared_ptr<Card> card)
{
    PrintCard(card);
}
