#ifndef __window_system_h
#define __window_system_h
#include "window.h"
#include <memory>
using namespace std;

namespace MyUno
{
	class GameManager;
	enum Windows
	{
		PlayerSetup,
		MainMatch,
		Victory,
		HelloWorld,
	};
	class WindowSystem
	{
	private:		
		shared_ptr<Window> currentWindow;
	public:
		GameManager& gameManager;
		WindowSystem(GameManager& gameManager);
		shared_ptr<Window> GetCurrentWindow();
		shared_ptr<Window> SwitchWindow(Windows window);
	};
}

#endif