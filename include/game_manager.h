#ifndef __game_manager_h
#define __game_manager_h
#include "window_system.h"
namespace MyUno
{
	/// <summary>
	/// Orchestrates the game.
	/// </summary>
	class GameManager
	{
	private:
		WindowSystem windowManager;
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
	};
}

#endif