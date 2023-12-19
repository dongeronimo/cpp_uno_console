#ifndef __match_window_h
#define __match_window_h
#include "window.h"
#include <vector>
#include <memory>

using namespace std;
namespace MyUno
{
	enum Type;
	class CardView;
	class WindowSystem;
	class MatchWindow : public Window
	{
	private:
		vector<shared_ptr<CardView>> cardViewProcessors;
		shared_ptr<CardView> GetCardView(MyUno::Type type);
	public:
		MatchWindow(WindowSystem& manager);
		void Draw();
		virtual ~MatchWindow() {}
	};
}

#endif