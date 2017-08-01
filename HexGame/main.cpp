#include <iostream>
#include <SFML\Graphics.hpp>

#include "Gui.h"
#include "TileManager.h"
#include "Common.h"

int main()
{
	sf::Font font;
	font.loadFromFile("Fonts/arial.ttf");
	// Create a text
	// Draw it

	Gui mainWindow;
	TileManager tm;
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