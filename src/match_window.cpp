#include "match_window.h"
#include <iostream>
#include "window_system.h"
#include "player.h"
#include "game_manager.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

MyUno::MatchWindow::MatchWindow(WindowSystem& manager) 
    : Window(manager)
{
}

void MyUno::MatchWindow::Draw()
{
    //foreach player
    auto players = windowSystem.gameManager.GetPlayers();
    for (auto playerIt = players.begin();playerIt != players.end();++playerIt)
    {
        shared_ptr<Player> currentPlayer = *playerIt;
        //clears the screen
        system("cls");
        //print it's cards
        vector<shared_ptr<Card>> cardsInHand = currentPlayer->GetCards();
        cout << "Your hand: ";
        for (auto cardsIt = cardsInHand.begin(); cardsIt != cardsInHand.end(); ++cardsIt)
        {
            shared_ptr<Card> currentCard = *cardsIt;

        }
        //prints the top card on the discard pile
        //asks which card the player will play
    }
}
