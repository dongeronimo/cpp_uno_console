#ifndef __window_victory_h
#define __window_victory_h
#include "window.h"
namespace MyUno
{
	class WindowSystem;
	class VictoryWindow : public Window
	{
	private:
	public:
		VictoryWindow(WindowSystem& manager);
		void Draw();
		virtual ~VictoryWindow() {}
	};
}

#endif