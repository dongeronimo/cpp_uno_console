#ifndef __window_h
#define __window_h

namespace MyUno
{
	class WindowSystem;
	class Window
	{
	protected:
		WindowSystem& windowSystem;
	public:
		Window(WindowSystem& manager);
		virtual void Draw() = 0;
		virtual ~Window() {}
	};
}

#endif