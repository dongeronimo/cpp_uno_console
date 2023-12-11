#include "window_system.h"
#include "window.h"
#include "window_hello_world.h"
using namespace MyUno;

WindowSystem::WindowSystem(GameManager& gameManager)
	:gameManager(gameManager)
{
}

shared_ptr<Window> WindowSystem::GetCurrentWindow()
{ 
	return currentWindow; 
}

shared_ptr<Window> WindowSystem::SwitchWindow(Windows window) 
{
	switch (window)
	{
	case MyUno::HelloWorld:
		{
			currentWindow = std::make_shared<WindowHelloWorld>(*this);
			break;
		}
	}
	return GetCurrentWindow();
}