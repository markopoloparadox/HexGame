#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
class Gui
{
public:
	Gui();
	~Gui();

	void ClearWindow() { m_win->clear();  m_win->setView(view); }

	void UserInput();
	void Update();
	void DisplayWindow() { m_win->display(); };

	bool isWindowsOpen() { return m_win->isOpen(); }
	sf::RenderWindow* GetWindow() { return m_win.get(); }

private:
	std::unique_ptr<sf::RenderWindow> m_win;
	sf::View view;
};

