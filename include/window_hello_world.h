#ifndef __window_hello_world_h
#define __window_hello_world_h
#include "window.h"
namespace MyUno
{
	class WindowManager;
	class WindowHelloWorld : public Window
	{
	private:
	public:
		WindowHelloWorld(WindowSystem& manager);
		void Draw();
	};
}

#endif