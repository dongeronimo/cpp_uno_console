#ifndef __game_manager_h
#define __game_manager_h
#include <string>
#include <memory>
#include <vector>
#include "window_system.h"
#include "deck_generator.h"
using namespace std;
namespace MyUno
{
	enum Increment{Positive=1, Negative=-1};
	class Player;
	/// <summary>
	/// Orchestrates the game.
	/// </summary>
	class GameManager
	{
	private:
		DeckGenerator deckGenerator;
		WindowSystem windowManager;
		shared_ptr<CardContainer> deck;
		shared_ptr<CardContainer> discardPile;
		vector<shared_ptr<Player>> players;
		void BuildPlayerHand(shared_ptr<Player> player);
		void RandomizePlayerOrder();
		bool isRunning;
		int currentPlayerId;
		Increment increment;
		GameManager();
		int plus2Stack;
	public:
		static GameManager& GetInstance()
		{
			static GameManager instance;
			return instance;
		}
		GameManager(GameManager const&) = delete;
		void operator=(GameManager const&) = delete;
		void Quit();
		void GameLoop();
		void BeginMatch(const vector<string>& playerNames);

		vector<shared_ptr<Player>> GetPlayers() 
		{
			return players;
		}
		shared_ptr<CardContainer> GetDeck() { return deck; }
		shared_ptr<CardContainer> GetDiscardPile() { return discardPile; }
		void PlayCard(shared_ptr<Player> player, shared_ptr<Card> card);
		shared_ptr<Card> DealCardTo(shared_ptr<Player> player);
		void RevertOrderOfMatch();
		void Jump();
		shared_ptr<Player> GetCurrentPlayer();
		shared_ptr<Player> GetPreviousPlayer();
		shared_ptr<Player> GetNextPlayer();
		void EndTurn();
		void IncreasePlus2Stack() { plus2Stack=plus2Stack+2; }
		bool IsResolvingPlus2() { return plus2Stack > 0; }
		vector<shared_ptr<Card>> ResolvePlus2(shared_ptr<Player> target);
		vector<shared_ptr<Player>> GetPlayersThatCalledUno();
		void PlayerCalledUno(shared_ptr<Player> p);
		void PlayerFailedToWin(shared_ptr<Player> p);
		shared_ptr<Player> GetVictor();
	};
}

#endif