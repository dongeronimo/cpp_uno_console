#include "game_manager.h"
#include <iostream>
using namespace MyUno;

GameManager::GameManager()
	:IsRunning(false)
{
}

void GameManager::Quit() 
{
	IsRunning = false;
}

void GameManager::GameLoop()
{
	IsRunning = true;
	while (IsRunning) {
		std::cout << "Begin game loop" << std::endl;
	}
}