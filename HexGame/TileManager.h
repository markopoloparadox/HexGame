#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <utility>

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\ConvexShape.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <JSON\json.hpp>

#include "Common.h"
#include "Tile.h"


class TileManager
{
public:
	TileManager();
	~TileManager();

	void LoadMap(const char* fileName);
	void LoadTileSet(const char* fileName);
	void Draw(sf::RenderWindow* win);
	void SetFont(sf::Font* font) { m_font = font; }

	std::string GetTileInfo(int posX, int posY);

private:
	void InitShapes();
	uInt FindTileByPosition(uInt mX, uInt mY);
	uInt FindMinimumRow(uInt posY);
	uInt FindMinimumCol(int posX);

	std::vector<Tile> m_tiles;
	std::vector<sf::ConvexShape> m_shapes;
	std::unordered_map<uShort, std::pair<std::string, sf::Texture>> m_background;
	std::unordered_map<uShort, std::pair<std::string, sf::Texture>> m_resource;

	sf::Font* m_font;

	uInt m_mapH = 0;
	uInt m_mapW = 0;

	uShort m_tileH = 0;
	uShort m_tileW = 0;
	uShort m_rows = 0;
	uShort m_cols = 0;

};

