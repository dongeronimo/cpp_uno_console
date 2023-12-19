#ifndef __create_players_window_h
#define __create_players_window_h
#include "window.h"
#include <vector>
#include <string>
namespace MyUno
{
	class WindowSystem;
	/// <summary>
	/// This is the form to create the players. It has a loop in which the 
	/// user inputs how many players and then a second loop in which the 
	/// player names are defined. Once all players are set it goes to the
	/// game window
	/// </summary>
	class CreatePlayerWindow : public Window
	{
	private:
		int numberOfPlayers;
		std::vector<std::string> playerNames;
		void ReadNumberOfPlayers();
		void ReadPlayerNames();
	public:
		CreatePlayerWindow(WindowSystem& manager);
		void Draw();
		virtual ~CreatePlayerWindow() = default;
	};
}

#endif