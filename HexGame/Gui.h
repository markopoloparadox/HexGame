#pragma once
#include <memory>
#include <SFML\Graphics.hpp>

#include "ToolTip.h"
#include "TileManager.h"
#include "Common.h"
class Gui
{
public:
	Gui();
	~Gui();

	void ClearWindow() { m_win->clear();  m_win->setView(view); }
	void UserInput();
	void Update();
	void DisplayWindow() { if(shouldRednerTT == true) m_tt.Draw(m_win.get()); m_win->display(); }
	void SetTileManager(TileManager* tm) { m_tm = tm; }

	bool isWindowsOpen() { return m_win->isOpen(); }
	sf::RenderWindow* GetWindow() { return m_win.get(); }

private:
	void OnLeftMouseClick();

	ToolTip m_tt;

	sf::Transform trans;
	sf::View view;
	sf::Font font;

	std::unique_ptr<sf::RenderWindow> m_win;

	TileManager* m_tm = nullptr;


	bool shouldRednerTT = false;
	bool isDone = false;
};

