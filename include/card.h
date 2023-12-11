#ifndef __card_h
#define __card_h
namespace MyUno
{
	enum Color {Red, Green, Blue, Yellow};
	enum Type {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Plus2, Reverse, Jump};

	class Card 
	{
	public:
		const unsigned int id;
		const Color color;
		const Type type;
		Card(Color color, Type type);
		virtual bool CanBePlayed() = 0;
		virtual void ExecuteAction() = 0;
	};
}
#endif