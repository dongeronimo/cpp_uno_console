#include "window_system.h"
#include "window.h"
#include "window_hello_world.h"
#include "create_players_window.h"
#include "match_window.h"
#include "victory_window.h"
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
		case MyUno::PlayerSetup:
		{
			currentWindow = std::make_shared<CreatePlayerWindow>(*this);
			break;
		}
		case MyUno::MainMatch:
		{
			currentWindow = std::make_shared<MatchWindow>(*this);
			break;
		}
		case MyUno::HelloWorld:
		{
			currentWindow = std::make_shared<WindowHelloWorld>(*this);
			break;
		}
		case MyUno::Victory:
		{
			currentWindow = std::make_shared<VictoryWindow>(*this);
			break;
		}
	}
	return GetCurrentWindow();
}