#include "card.h"
static int counter = 0;
MyUno::Card::Card(Color color, Type type)
	:color(color), type(type), id(++counter)
{
}

std::string MyUno::TypeToString(Type t)
{
	switch (t)
	{
	case MyUno::Zero:
		return "0";
	case MyUno::One:
		return "1";
	case MyUno::Two:
		return "2";
	case MyUno::Three:
		return "3";
	case MyUno::Four:
		return "4";
	case MyUno::Five:
		return "5";
	case MyUno::Six:
		return "6";
	case MyUno::Seven:
		return "7";
	case MyUno::Eight:
		return "8";
	case MyUno::Nine:
		return "9";
	case MyUno::Plus2:
		return "+2";
	case MyUno::Reverse:
		return "R";
	case MyUno::Jump:
		return "J";

	}
}
