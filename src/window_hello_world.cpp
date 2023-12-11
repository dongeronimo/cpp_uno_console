#include "window_hello_world.h"
#include <iostream>
#include <conio.h>
#include "window_system.h"
#include "game_manager.h"
using namespace MyUno;
using namespace std;
WindowHelloWorld::WindowHelloWorld(WindowSystem& manager) : Window(manager)
{
	std::cout << "Criou a WindowHelloWorld" << std::endl;
}

void WindowHelloWorld::Draw()
{
	cout << "Press q to quit or any other key to continue..." << endl;
	char in = _getch();
	if (in == 'q') {
		windowSystem.gameManager.Quit();
	}
}
