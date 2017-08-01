#include <iostream>
#include <memory>
#include <SFML\Graphics.hpp>

#include "TileManager.h"
#include "Common.h"

int main()
{
	uInt w = 800;
	uInt h = 600;
 	std::string winName = "Test";


	sf::Font font;
	font.loadFromFile("Fonts/arial.ttf");
	// Create a text
	// Draw it

	std::unique_ptr<sf::RenderWindow> m_win;

	m_win = std::make_unique<sf::RenderWindow>(sf::VideoMode(w, h), winName);
	m_win->setFramerateLimit(60);

	TileManager tm;
	tm.LoadMap("Maps/map1.json");
	tm.font = &font;


	while (m_win->isOpen())
	{
		sf::Event event;
		while (m_win->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				m_win->close();
			}
		}

		m_win->clear();
		tm.Draw(m_win.get());
		m_win->display();
	}

	return EXIT_SUCCESS;
}