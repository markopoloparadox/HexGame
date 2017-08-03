#include "ToolTip.h"



ToolTip::ToolTip()
{
	m_shape.setSize(sf::Vector2f(100.0f, 50.0f));
	m_shape.setFillColor(sf::Color(100, 100, 100, 200));

	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(10);
}


ToolTip::~ToolTip()
{
}

void ToolTip::SetPosition(float x, float y)
{
	m_shape.setPosition(x + 15, y);
	m_text.setPosition(x + 15, y);
}

void ToolTip::Draw(sf::RenderWindow * win)
{
	win->draw(m_shape);
	win->draw(m_text);
}
