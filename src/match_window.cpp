#include "match_window.h"
#include <iostream>
#include "window_system.h"
#include "player.h"
#include "game_manager.h"
#include <stdlib.h>
#include <stdexcept>
#include <stdio.h>
#include "card_view.h"
#include "numeric_card_view.h"
using namespace std;
using namespace MyUno;
shared_ptr<CardView> MyUno::MatchWindow::GetCardView(MyUno::Type type)
{
    for(auto cardView: cardViewProcessors)
    {
        if (cardView->CanProcess(type))
            return cardView;
    }
    throw std::logic_error("can't find a processor. There must be a processor for each type. Take a look at the ctor of MatchWindow");
}

MyUno::MatchWindow::MatchWindow(WindowSystem& manager)
    : Window(manager)
{
    auto numericCardProcessor = std::make_shared<NumericCardView>();
    cardViewProcessors.push_back(numericCardProcessor);
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
        cout << currentPlayer->name << endl;
        cout << "Your hand: ";
        for (auto cardsIt = cardsInHand.begin(); cardsIt != cardsInHand.end(); ++cardsIt)
        {
            shared_ptr<Card> currentCard = *cardsIt;
            shared_ptr<CardView> cardView = GetCardView(currentCard->type);
            cardView->Draw(currentCard);
        }
        cout << endl;
        //prints the top card on the discard pile
        std::shared_ptr<Card> topDiscardPile = windowSystem.gameManager.GetDiscardPile()->Top();
        cout << "Discard Pile top: ";
        if (topDiscardPile != nullptr) 
        {
            GetCardView(topDiscardPile->type)->Draw(topDiscardPile);
        }
        else 
        {
            cout << "Is empty.";
        }
        cout << endl;
        //asks which card the player will play
        string input;
        cin >> input;
    }
}
