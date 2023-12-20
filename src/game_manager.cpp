#include "game_manager.h"
#include <iostream>
#include <random>
#include "player.h"
using namespace MyUno;


GameManager::GameManager()
	:isRunning(false),
	windowManager(WindowSystem(*this))
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
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(players.begin(), players.end(), g);
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

void MyUno::GameManager::PlayCard(shared_ptr<Player> player, shared_ptr<Card> card)
{
	//Tirar uma carta da mão do player
	//Po-la na pilha de descarte
}

shared_ptr<Card> MyUno::GameManager::DealCardTo(shared_ptr<Player> player)
{
	//tirar uma carta da pilha de compra
	//se pilha de compra ficar vazia, pegar toda a pilha de descarte, tranferir pra pilha de compra e reembaralhar.
	return shared_ptr<Card>();
}
