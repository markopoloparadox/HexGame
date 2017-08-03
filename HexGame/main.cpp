#include <iostream>
#include <SFML\Graphics.hpp>

#include "Gui.h"
#include "TileManager.h"
#include "Common.h"

int main()
{
	// Create a text
	// Draw it

	Gui mainWindow;
	TileManager tm;
	mainWindow.SetTileManager(&tm);
	tm.LoadMap("Maps/map1.json");


	while (mainWindow.isWindowsOpen())
	{
		mainWindow.ClearWindow();
		mainWindow.Update();
		tm.Draw(mainWindow.GetWindow());
		mainWindow.DisplayWindow();
	}

	return EXIT_SUCCESS;
}