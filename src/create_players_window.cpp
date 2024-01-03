#include "create_players_window.h"
#include <iostream>
#include <stdexcept>
#include "string_utils.h"
#include "window_system.h"
#include "game_manager.h"
using namespace std;

MyUno::CreatePlayerWindow::CreatePlayerWindow(WindowSystem& manager)
    : Window(manager, PlayerSetup)
{
}

void MyUno::CreatePlayerWindow::ReadNumberOfPlayers()
{
    bool validInput = false;
    while (!validInput) {
        cout << "How many players? ";
        string tempInput;
        cin >> tempInput;
        try {
            numberOfPlayers = stoi(tempInput);
        }
        catch (const logic_error& ) {
            cout << "It must be a number." << endl;
            continue;
        }
        if (numberOfPlayers <= 0)
            cout << "It makes no sense to have negative players" << endl;
        else if (numberOfPlayers < 2)
            cout << "Need at least 2 players" << endl;
        else if (numberOfPlayers > 10)
            cout << "Too many players" << endl;
        else
            validInput = true;
    }
    cout << "Now, the name of the players:" << endl;
}

void MyUno::CreatePlayerWindow::ReadPlayerNames()
{
    while (playerNames.size() < numberOfPlayers)
    {
        cout << "Player " << playerNames.size() + 1 << " name: ";
        string tempInput;
        cin >> tempInput;
        const string trimmedString = trim(tempInput);
        if (trimmedString.size() == 0)
        {
            cout << "Please provide a name" << endl;
        }
        else 
        {
            playerNames.push_back(trimmedString);
        }
    }
    windowSystem.gameManager.BeginMatch(playerNames);
    cout << "Done. Beginning the match" << endl;
}

void MyUno::CreatePlayerWindow::Draw()
{
    ReadNumberOfPlayers();
    ReadPlayerNames();
}
