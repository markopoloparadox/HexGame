#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>	
#include <SFML\Graphics\Text.hpp>

#include "Common.h"
class ToolTip
{
public:
	ToolTip();
	~ToolTip();
	
	void SetPosition(float x, float y);
	void SetFont(sf::Font* font) { m_text.setFont(*font); }
	void SetText(std::string text) { m_text.setString(text); };
	void AddText(std::string text) { m_text.setString(m_text.getString() + text); };
	void Draw(sf::RenderWindow* win);
private:
	sf::RectangleShape m_shape;
	sf::Text m_text;
};

