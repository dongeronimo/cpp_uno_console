#include "card.h"
static int counter = 0;
MyUno::Card::Card(Color color, Type type)
	:color(color), type(type), id(++counter)
{
}
