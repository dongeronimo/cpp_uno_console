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
		const int Id;
		Window(WindowSystem& manager, int id);
		virtual void Draw() = 0;
		virtual ~Window() {}
	};
}

#endif