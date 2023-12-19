#ifndef __card_h
#define __card_h
#include <string>
namespace MyUno
{
	enum Color {Red, Green, Blue, Yellow};
	enum Type {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Plus2, Reverse, Jump};

	std::string TypeToString(Type t);

	class Card 
	{
	public:
		const unsigned int id;
		const Color color;
		const Type type;
		Card(Color color, Type type);
		virtual bool CanBePlayed() = 0;
		virtual void ExecuteAction() = 0;
		bool operator==(const Card& other) const {
			return id == other.id;
		}
		bool operator!=(const Card& other) const {
			return !(*this == other);
		}
		virtual ~Card() {}
	};
}
#endif