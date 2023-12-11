#include "game_manager.h"
#include <iostream>
using namespace MyUno;

GameManager::GameManager()
	:isRunning(false),
	windowManager(WindowSystem(*this))
{
}

void GameManager::Quit() 
{
	isRunning = false;
}

void GameManager::GameLoop()
{
	isRunning = true;
	windowManager.SwitchWindow(HelloWorld);
	while (isRunning) {
		windowManager.GetCurrentWindow()->Draw();
		std::cout << "Begin game loop" << std::endl;
	}
}