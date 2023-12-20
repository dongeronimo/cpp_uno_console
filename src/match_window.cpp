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
    for (auto cardView : cardViewProcessors)
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
    for (auto playerIt = players.begin(); playerIt != players.end(); ++playerIt)
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
        //TODO: Verificar se h� possibilidade de jogar alguma carta
        if (currentPlayer->CanPlayAnyCard(topDiscardPile.get()))
        {//TODO: Se houver ent�o pede pro player jogar
            auto chosenCard = ChooseCard(cardsInHand, topDiscardPile);
            windowSystem.gameManager.PlayCard(currentPlayer, chosenCard);
        }
        else
        {//TODO: Se n�o houver pede pro gameManager dar carta pro player
            auto dealtCard = windowSystem.gameManager.DealCardTo(currentPlayer);
            cout << "You got ";
            GetCardView(dealtCard->type)->Draw(dealtCard);
            cout << endl << "Press any key to continue.";
            string trash;
            cin >> trash;
        }
    }

}
shared_ptr<Card> MyUno::MatchWindow::ChooseCard(const vector<shared_ptr<Card>>& cardsInHand, const std::shared_ptr<Card>& topDiscardPile)
{
    bool cardCantBePlayed = true;
    shared_ptr<Card> chosenCard = nullptr;
    while (cardCantBePlayed)
    {
        //asks which card the player will play
        chosenCard = cardsInHand[AskForCard(cardsInHand)];
        //Can he play it?
        cardCantBePlayed = !chosenCard->CanBePlayed(topDiscardPile.get());
        if (cardCantBePlayed)
        {
            cout << "Can't play this card, choose another." << std::endl;
        }
    }
    return chosenCard;
}
int MatchWindow::AskForCard(const vector<shared_ptr<Card>>& cardsInHand)
{
    bool validCardPosValue = false;
    int cardToPlayIndex = -1;
    while (!validCardPosValue)
    {
        cout << "Which card will you play? Type it's position in your hand: ";
        string input;
        try
        {
            cin >> input;
            int positionInHand = std::stoi(input) - 1;
            if (positionInHand < 0 || positionInHand >= cardsInHand.size()) {
                cout << "Should be between 1 and " << cardsInHand.size() << endl;
            }
            else
            {
                cardToPlayIndex = positionInHand;
                validCardPosValue = true;
            }
        }
        catch (std::logic_error)
        {
            cout << "Should be between 1 and " << cardsInHand.size() << endl;
        }
    }
    return cardToPlayIndex;
}

