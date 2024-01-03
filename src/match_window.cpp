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
#include "reverse_card_view.h"
#include "jump_card_view.h"
#include "plus2_card_view.h"
#include <algorithm>
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
    : Window(manager, MainMatch)
{
    auto numericCardProcessor = std::make_shared<NumericCardView>();
    cardViewProcessors.push_back(numericCardProcessor);
    auto reverseCardProcessor = std::make_shared<ReverseCardView>();
    cardViewProcessors.push_back(reverseCardProcessor);
    auto jumpCardProcessor = std::make_shared<JumpCardView>();
    cardViewProcessors.push_back(jumpCardProcessor);
    auto plus2CardProcessor = std::make_shared<Plus2CardView>();
    cardViewProcessors.push_back(plus2CardProcessor);
}

void MyUno::MatchWindow::Draw()
{
    shared_ptr<Player> currentPlayer = windowSystem.gameManager.GetCurrentPlayer();
    shared_ptr<Player> previousPlayer = windowSystem.gameManager.GetPreviousPlayer();
    shared_ptr<Player> nextPlayer = windowSystem.gameManager.GetNextPlayer();
 
    //clears the screen
    system("cls");
    //print it's cards
    vector<shared_ptr<Card>> cardsInHand = currentPlayer->GetCards();
    cout << "previous player: " << previousPlayer->name << endl;
    cout << "current player (you): " << currentPlayer->name << endl;
    cout << "next player: " << nextPlayer->name << endl;
    auto playersThatCalledUno = GameManager::GetInstance().GetPlayersThatCalledUno();
    for (auto calledUno : playersThatCalledUno)
    {
        cout << calledUno->name << " called uno!" << endl;
    }
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
    
    if (GameManager::GetInstance().IsResolvingPlus2())
    {
        if (currentPlayer->HasPlus2())
        {
            auto chosenCard = AskForPlus2(cardsInHand);
            GameManager::GetInstance().PlayCard(currentPlayer, chosenCard);
        }
        else
        {
            auto boughtCards = GameManager::GetInstance().ResolvePlus2(currentPlayer);
            cout << "You bought:";
            for (auto card : boughtCards)
            {
                GetCardView(card->type)->Draw(card);
            }
            cout << endl;
        }
        cout << endl << "Press any key to continue.";
        string trash;
        cin >> trash;
    }
    else 
    {
        if (currentPlayer->CanPlayAnyCard(topDiscardPile.get()))
        {
            if (currentPlayer->CanCallUno())
            {
                bool wantsToCallUno = AskIfItWantToCallUno();
                if (wantsToCallUno)
                {
                    GameManager::GetInstance().PlayerCalledUno(currentPlayer);
                }
            }
            auto chosenCard = ChooseCard(cardsInHand, topDiscardPile);
            windowSystem.gameManager.PlayCard(currentPlayer, chosenCard);

        }
        else
        {
            if (currentPlayer->CalledUno() || cardsInHand.size() == 1) {
                auto dealtCard = windowSystem.gameManager.DealCardTo(currentPlayer);
                cout << "You got ";
                GetCardView(dealtCard->type)->Draw(dealtCard);
                GameManager::GetInstance().PlayerFailedToWin(currentPlayer);
            }
            else {
                auto dealtCard = windowSystem.gameManager.DealCardTo(currentPlayer);
                cout << "You got ";
                GetCardView(dealtCard->type)->Draw(dealtCard);
            }
            cout << endl << "Press any key to continue.";
            string trash;
            cin >> trash;
        }
    }
    windowSystem.gameManager.EndTurn();

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

shared_ptr<Card> MyUno::MatchWindow::AskForPlus2(const vector<shared_ptr<Card>>& cardsInHand)
{
    vector<int> plus2Idx;
    for (auto i = 0; i < cardsInHand.size(); i++)
    {
        auto currCard = cardsInHand[i];
        if (currCard->type == Plus2)
            plus2Idx.push_back(i);
    }
    bool playingAPlus2 = false;
    shared_ptr<Card> chosenCard = nullptr;
    while (!playingAPlus2) {
        cout << "You have to play one of your +2 cards (";
        for (auto i : plus2Idx)
            cout << i+1 << ",";
        cout << "):";
        string str;
        cin >> str;
        try {
            int idx = stoi(str) - 1;
            bool isInsideIdx = false;
            for (auto i : plus2Idx)
            {
                if (i == idx)
                    isInsideIdx = true;
            }
            if (!isInsideIdx) {
                cout << "Must be one of the +2 cards" << endl;
            }
            else {
                playingAPlus2 = true;
                chosenCard = cardsInHand[idx];
            }
        }
        catch (std::logic_error&)
        {
            cout << "Invalid number" << endl;
        }
    }
    return chosenCard;
}

bool MyUno::MatchWindow::AskIfItWantToCallUno()
{
    bool choseOption = false;
    string input="";
    while (!choseOption)
    {
        cout << "Do you want to call uno (y/n) ?";
        cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        if (input == "Y" || input == "N") {
            choseOption = true;
        }
        else {
            cout << "Not a valid option" << endl;
        }
    }
    if (input == "Y")
        return true;
    else
        return false;
}




