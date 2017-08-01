#include "Gui.h"

Gui::Gui()
{
	m_win = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024,768), "HexGame");
	m_win->setFramerateLimit(60);
	view.setSize(m_win->getSize().x, m_win->getSize().y);
	view.setCenter(m_win->getSize().x/3, m_win->getSize().y / 3);
}


Gui::~Gui()
{
}

void Gui::UserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		view.move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		view.move(10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		view.move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		view.move(0, 10);
	}
}

void Gui::Update()
{
	UserInput();

	sf::Event event;
	while (m_win->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			m_win->close();
		}
		if (event.type == sf::Event::MouseWheelScrolled) {
			if (event.mouseWheelScroll.delta > 0) {
				view.zoom(0.9f);
			}
			else {
				view.zoom(1.1f);
			}
		}
		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			view.setSize(event.size.width, event.size.height);
		}
	}
}
