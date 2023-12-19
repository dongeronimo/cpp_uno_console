#ifndef __match_window_h
#define __match_window_h
#include "window.h"
#include "card_view.h"
namespace MyUno
{
	class WindowSystem;
	class MatchWindow : public Window
	{
	private:

	public:
		MatchWindow(WindowSystem& manager);
		void Draw();
		virtual ~MatchWindow() {}
	};
}

#endif