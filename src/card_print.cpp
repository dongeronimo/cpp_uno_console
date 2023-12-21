#include "card_print.h"
#include <color.hpp>
#include <card.h>
using namespace std;
void MyUno::PrintCard(const std::shared_ptr<Card> card)
{
    switch (card->color)
    {
    case Red:
        cout << hue::red << "|" << TypeToString(card->type) << "|" << hue::reset;
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
