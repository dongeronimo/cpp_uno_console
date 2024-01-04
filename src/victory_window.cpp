#include "victory_window.h"
#include "window_system.h"
#include "game_manager.h"
#include <iostream>
#include <player.h>
MyUno::VictoryWindow::VictoryWindow(WindowSystem& manager)
    : Window(manager, Victory)
{
}

void MyUno::VictoryWindow::Draw()
{
    system("cls");
    auto winner = GameManager::GetInstance().GetVictor();
    std::cout << winner->name << " won." << std::endl;
    std::cout << "Press any key to finish game.";
    string trash;
    std::cin >> trash;
    GameManager::GetInstance().Quit();
}
