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
	public:
		GameManager();
		/// <summary>
		/// End the main game loop by setting IsRunning to false. The next time the game loop
		/// is evaluated it'll evaluate to false
		/// </summary>
		void Quit();
		/// <summary>
		/// The main loop is here. Execution will enter here and only leaves when
		/// GameManager.Quit is invoked
		/// </summary>
		void GameLoop();
		/// <summary>
		/// Shuffles the initial deck, create the players, give them their cards from
		/// the deck and go to the match window.
		/// </summary>
		/// <param name="playerNames"></param>
		void BeginMatch(const vector<string>& playerNames);

		vector<shared_ptr<Player>> GetPlayers() 
		{
			return players;
		}
		shared_ptr<CardContainer> GetDeck() { return deck; }
		shared_ptr<CardContainer> GetDiscardPile() { return discardPile; }
		void PlayCard(shared_ptr<Player> player, shared_ptr<Card> card);
		shared_ptr<Card> DealCardTo(shared_ptr<Player> player);
	};
}

#endif