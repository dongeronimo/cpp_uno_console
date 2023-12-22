#include "game_manager.h"
#include <iostream>
#include <random>
#include "player.h"
#include "random.h"
using namespace MyUno;


GameManager::GameManager()
	:isRunning(false),
	windowManager(WindowSystem(*this)),
	currentPlayerId(0),
	increment(Positive),
	plus2Stack(0)
{
}

void GameManager::Quit() 
{
	isRunning = false;
}

void GameManager::GameLoop()
{
	isRunning = true;
	windowManager.SwitchWindow(PlayerSetup);
	while (isRunning) {
		windowManager.GetCurrentWindow()->Draw();
	}
}
void MyUno::GameManager::BuildPlayerHand(shared_ptr<Player> player)
{
	for (auto i = 0; i < 7; i++)
	{
		shared_ptr<Card> topCard = deck->BuyTopCard();
		player->GiveCard(topCard);
	}
}

void MyUno::GameManager::RandomizePlayerOrder()
{
#ifndef NO_RANDOM_ORDERING
	std::shuffle(players.begin(), players.end(), MyRandom::GetInstance().GetGenerator());
#endif 
}

void MyUno::GameManager::BeginMatch(const vector<string>& playerNames)
{
	auto localGenerated = deckGenerator.Generate();
	deck = std::make_shared<CardContainer>(localGenerated.GetCards());
	discardPile = std::make_shared<CardContainer>(); //Discard Pile begins empty
	players.clear();
	for (auto nameIt = playerNames.begin(); nameIt != playerNames.end(); ++nameIt)
	{
		auto currentName = *nameIt;
		shared_ptr<Player> newPlayer = make_shared<Player>(currentName);
		BuildPlayerHand(newPlayer);
		players.push_back(newPlayer);
	}
	RandomizePlayerOrder();
	windowManager.SwitchWindow(MainMatch);
}

void MyUno::GameManager::PlayCard(shared_ptr<Player> player, shared_ptr<Card> chosenCard)
{
	player->RemoveCardFromHand(chosenCard);
	discardPile->Add(chosenCard);
	chosenCard->ExecuteAction();
}

shared_ptr<Card> MyUno::GameManager::DealCardTo(shared_ptr<Player> player)
{
	auto card = deck->BuyTopCard();
	if (deck->Count() == 0)
	{
		auto topDiscardPile = discardPile->BuyTopCard();
		//TODO: criar um bulk move pra mover todas de uma vez.
		while (discardPile->Count() > 0) 
		{
			auto bought = discardPile->BuyTopCard();
			deck->Add(bought);
		}
		deck->Shuffle();
		discardPile->Add(topDiscardPile);//Volta com a carta pro topo
	}
	player->GiveCard(card);
	return card;
}

void MyUno::GameManager::RevertOrderOfMatch()
{
	increment = increment == Positive ? Negative : Positive;
	
}

void MyUno::GameManager::Jump()
{
	currentPlayerId = currentPlayerId + increment;//end turn alredy increments player. so incrementing here guarantees that the player will be jumped
}



shared_ptr<Player> MyUno::GameManager::GetCurrentPlayer()
{
	return players[currentPlayerId % players.size()];
}

shared_ptr<Player> MyUno::GameManager::GetPreviousPlayer()
{
	if (increment == Positive)
	{
		return players[(currentPlayerId - Positive) % players.size()];
	}
	else
	{
		return players[(currentPlayerId - Negative) % players.size()];
	}
}

shared_ptr<Player> MyUno::GameManager::GetNextPlayer()
{
	if (increment == Positive)
	{
		return players[(currentPlayerId + Positive) % players.size()];
	}
	else
	{
		return players[(currentPlayerId + Negative) % players.size()];
	}
}

void MyUno::GameManager::EndTurn()
{
	currentPlayerId = currentPlayerId + increment;
	
}

vector<shared_ptr<Card>> MyUno::GameManager::ResolvePlus2(shared_ptr<Player> target)
{
	vector<shared_ptr<Card>> dealtCards;
	while (plus2Stack > 0) 
	{
		auto cardDealt = DealCardTo(target);
		dealtCards.push_back(cardDealt);
		plus2Stack--;
	}
	return dealtCards;
}
