#ifndef __window_hello_world_h
#define __window_hello_world_h
#include "window.h"
namespace MyUno
{
	class WindowSystem;
	class WindowHelloWorld : public Window
	{
	private:
	public:
		WindowHelloWorld(WindowSystem& manager);
		void Draw();
		virtual ~WindowHelloWorld() {}
	};
}

#endif