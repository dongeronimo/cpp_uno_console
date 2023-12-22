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
    //TODO: Avaliar se está rolando +2. Se estiver o player tem que jogar a +2 que tiver ou comprar o stack de +2
    if (GameManager::GetInstance().IsResolvingPlus2())
    {
        if (currentPlayer->HasPlus2())
        {//TODO: Se ele tem +2 ele é obrigado a jogar uma das +2
            auto chosenCard = AskForPlus2(cardsInHand);
            //agora que eu tenho o card +2 escolhido joga ele
            GameManager::GetInstance().PlayCard(currentPlayer, chosenCard);
        }
        else
        {//TODO: Se ele n tem ele é obrigado a resolver a pilha de +2 comprando
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
    else //nao ta resolvendo +2, player pode jogar qqer carta.
    {
        if (currentPlayer->CanPlayAnyCard(topDiscardPile.get()))
        {
            auto chosenCard = ChooseCard(cardsInHand, topDiscardPile);
            windowSystem.gameManager.PlayCard(currentPlayer, chosenCard);
        }
        else
        {
            auto dealtCard = windowSystem.gameManager.DealCardTo(currentPlayer);
            cout << "You got ";
            GetCardView(dealtCard->type)->Draw(dealtCard);
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
            cout << i << ",";
        cout << "):";
        string str;
        cin >> str;
        try {
            int idx = stoi(str);
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




