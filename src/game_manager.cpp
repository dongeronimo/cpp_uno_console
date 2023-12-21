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
	increment(Positive)
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
//3	std::shuffle(players.begin(), players.end(), MyRandom::GetInstance().GetGenerator());
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
	if (increment == Positive) 
	{
		increment = Negative;
		return;
	}
	if (increment == Negative)
	{
		increment = Positive;
		return;
	}
}

shared_ptr<Player> MyUno::GameManager::GetCurrentPlayer()
{
	return players[currentPlayerId];
}

shared_ptr<Player> MyUno::GameManager::GetPreviousPlayer()
{
	if (increment == Positive)
	{//incremento positivo, overflow no começo
		if (currentPlayerId - Positive < 0) {
			return players[players.size()-1];
		}
		else {
			return players[currentPlayerId - Positive];
		}
	}
	else
	{
		if (currentPlayerId - Negative >= players.size()) {
			return players[0];
		}
		else {
			return players[currentPlayerId - Negative];
		}
	}
}

shared_ptr<Player> MyUno::GameManager::GetNextPlayer()
{
	if (increment == Positive)
	{//Incremento positivo, overflow no final
		if (currentPlayerId + Positive >= players.size()) {
			return players[0];
		}
		else {
			return players[currentPlayerId + Positive];
		}
	}
	else
	{//incremento negativo, overflow no inicio
		if (currentPlayerId + Negative < 0) {
			return players[players.size() - 1];
		}
		else {
			return players[currentPlayerId + Negative];
		}
	}
}

void MyUno::GameManager::EndTurn()
{
	currentPlayerId = currentPlayerId + increment;
	if (currentPlayerId < 0)
	{
		currentPlayerId = players.size() - 1;
		return;
	}
	if (currentPlayerId >= players.size())
	{
		currentPlayerId = 0;
		return;
	}
		
}
