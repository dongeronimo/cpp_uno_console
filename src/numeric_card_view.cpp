#include "numeric_card_view.h"
#include "color.hpp"
using namespace MyUno;
std::vector<Type> numericTypes = { Type::Zero, Type::One, Type::Two, Type::Three,
    Type::Four, Type::Five, Type::Six, Type::Seven, Type::Eight, Type::Nine};

MyUno::NumericCardView::NumericCardView()
    :CardView(numericTypes)
{
}

void MyUno::NumericCardView::Draw(shared_ptr<Card> card)
{
    switch (card->color)
    {
    case Red:
        cout <<hue::red<<"|"<< TypeToString(card->type) <<"|"<<hue::reset;
        break;
    case Green:
        cout << hue::green << "|" << TypeToString(card->type) << "|" << hue::reset;
        break;
    case Blue:
        cout << hue::blue << "|" << TypeToString(card->type) << "|" << hue::reset;
        break;
    case Yellow:
        cout << hue::yellow << "|" << TypeToString(card->type) << "|" << hue::reset;
        break;
    }
}
