#include "Gui.h"

Gui::Gui()
{
	font.loadFromFile("Fonts/arial.ttf");

	m_win = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024,768), "HexGame");
	m_win->setFramerateLimit(60);
	view.setSize(m_win->getSize().x, m_win->getSize().y);
	view.setCenter(m_win->getSize().x/3, m_win->getSize().y / 3);

	m_tt.SetFont(&font);

	//view.setRotation(45.0f);
	//view.setSize(m_win->getSize().x, m_win->getSize().y * 2);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		view.rotate(1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		view.rotate(-1.0f);
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
		if (event.type == sf::Event::MouseWheelScrolled) 
		{
			if (event.mouseWheelScroll.delta > 0) {
				view.zoom(0.9f);
			}
			else {
				view.zoom(1.1f);
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			OnLeftMouseClick();
		}

		if (event.type == sf::Event::MouseMoved) {
			shouldRednerTT = false;
		}

		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			view.setSize(event.size.width, event.size.height);
		}
	}
}


void Gui::OnLeftMouseClick()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*m_win);
	// convert it to world coordinates
	sf::Vector2f worldPos = m_win->mapPixelToCoords(pixelPos, view);
	if (worldPos.x < 0 || worldPos.y < 0) {
		return;
	}

	m_tt.SetPosition(worldPos.x, worldPos.y);
	m_tt.SetText(m_tm->GetTileInfo(worldPos.x, worldPos.y));
	shouldRednerTT = true;

	//m_winHelp.reset(nullptr);
	//m_winHelp = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 768), "HexGame");
}
