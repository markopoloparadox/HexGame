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
	void LoadTiles(const char* fileName);
	void Draw(sf::RenderWindow* win);
	sf::Font* font;

private:
	void InitShapes();
	uInt FindTileByPosition(int posX, int posY);
	uInt FindMinimumRow(uInt posY);
	uInt FindMinimumCol(int posX);

	std::vector<Tile> m_tiles;
	std::vector<sf::ConvexShape> m_shapes;
	std::unordered_map<uShort, std::pair<std::string, sf::Texture>> m_backgrounds;
	std::unordered_map<uShort, std::pair<std::string, sf::Texture>> m_surfaces;

	uShort m_rows = 0;
	uShort m_cols = 0;
	uInt m_mapHeight = 0;
	uInt m_mapWidth = 0;

};

