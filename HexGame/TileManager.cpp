#include "TileManager.h"

#include <SFML\Graphics.hpp>

TileManager::TileManager()
{

}



TileManager::~TileManager()
{
}



void TileManager::InitShapes()
{
	for (uInt i = 0;  i < m_shapes.size(); ++i)
	{
		m_shapes[i].setPointCount(6);
		m_shapes[i].setPoint(0, sf::Vector2f(TILE_W * 0.5f, 0.0f));
		m_shapes[i].setPoint(1, sf::Vector2f(TILE_W, TILE_H *  0.25f));
		m_shapes[i].setPoint(2, sf::Vector2f(TILE_W, TILE_H *  0.75f));
		m_shapes[i].setPoint(3, sf::Vector2f(TILE_W * 0.5f, TILE_H));
		m_shapes[i].setPoint(4, sf::Vector2f(0.0f, TILE_H *  0.75f));
		m_shapes[i].setPoint(5, sf::Vector2f(0.0f, TILE_H *  0.25f));

		m_shapes[i].setOutlineColor(sf::Color::Red);
		m_shapes[i].setOutlineThickness(1);
		
		uShort r = m_tiles[i].m_r;
		uShort c = m_tiles[i].m_c;

		if (r % 2 == 0) {
			m_shapes[i].setPosition((float)(TILE_W) * c, TILE_H * r * 0.75f);
		}
		else {
			m_shapes[i].setPosition(TILE_W * c + TILE_W * 0.5, TILE_H * r * 0.75f);
		}
	}
}

uInt TileManager::FindTileByPosition(int posX, int posY)
{

	uInt mX = posX;
	uInt mY = posY;

	if (mX > m_mapWidth || mY > m_mapHeight) {
		return uIError;
	}

	double res = TILE_H * 0.55;
	bool found = false;
	uInt id = 0;
	uInt numOfComp = 0;

	uInt minId = FindMinimumRow(mY) * m_cols;
	uInt maxId = minId + (m_cols * 2);

	for (uInt i = minId; i < m_shapes.size(); ++i)
	{
		if (i >maxId) {
			break;
		}

		numOfComp++;
		uInt xTemp = m_shapes[i].getPosition().x + TILE_W * 0.5;
		uInt yTemp = m_shapes[i].getPosition().y + TILE_H * 0.5;

		uInt A = 0;
		uInt B = 0;

		mX > xTemp == true ? A = pow(mX - xTemp, 2) : A = pow(xTemp - mX, 2);
		mY > yTemp == true ? B = pow(mY - yTemp, 2) : B = pow(yTemp - mY, 2);

		double resTep = sqrt(A + B);

		if (resTep < res) 
		{
			found = true;
			res = resTep;
			id = i;
		}
	}

	if (found == true) {
		return id;
	}

	return uIError;
}

uInt TileManager::FindMinimumRow(uInt posY)
{
	if (posY < TILE_H) {
		return 0;
	}
	if (posY > (m_mapHeight - TILE_H * 0.75)) {
		return m_rows - 1;
	}
	
	uInt currPos = 0;

	for (uInt i = 0; i < m_rows; ++i) 
	{
		if (i == 0) {
			currPos += TILE_H;
		}
		else {
			currPos += (uInt)(TILE_H * 0.75);
		}

		if (posY < currPos) {
			return i;
		}
	}

	return 0;
}

uInt TileManager::FindMinimumCol(int posX)
{

	return 0;
}



void TileManager::LoadMap(const char * fileName)
{
	std::ifstream i(fileName);

	nlohmann::json js;
	i >> js;

	std::cout << "Input map file: " << fileName << "\n" << js << "\n";


	m_rows = js["Rows"].get<uShort>();
	m_cols = js["Cols"].get<uShort>();
	
	// Create Tiles and shapes
	m_tiles.reserve(m_rows * m_cols);
	m_shapes.reserve(m_rows * m_cols);
	for (uShort r = 0; r < m_rows; ++r) 
	{
		for (uShort c = 0; c < m_cols; ++c) 
		{
			m_shapes.push_back(sf::ConvexShape());
			m_tiles.push_back(Tile());
			m_tiles.back().m_r = r;
			m_tiles.back().m_c = c;
		}
	}
	
	InitShapes();

	for (uInt i = 0; i < m_rows * m_cols; ++i) 
	{
		m_tiles[i].m_backId = js["Background_data"][i].get<uShort>();
		m_tiles[i].m_surfId = js["Surface_data"][i].get<uShort>();
		m_tiles[i].m_shapeId = i;
	}

	m_mapWidth = m_cols * TILE_W;
	m_mapHeight = TILE_H;
	if (m_rows > 1) {
		m_mapHeight += TILE_H * 0.75 * (m_rows - 1);
		m_mapWidth += TILE_W * 0.50;
	}
}

void TileManager::LoadTiles(const char * fileName)
{
	std::ifstream i(fileName);

	nlohmann::json js;
	i >> js;

	std::cout << "Input tile file: " << fileName << "\n" << js << "\n";

	if (js.find("Background") != js.end()) 
	{
		for (auto& tile : js["Background"]) {
			uShort id = tile["Id"].get<uShort>();
			std::string name = tile["Name"].get<std::string>();
			std::string fileLoc = tile["File"].get<std::string>();

			m_backgrounds[id] = std::make_pair(name, sf::Texture());
			m_backgrounds[id].second.loadFromFile(fileLoc);
		}
	}
	if (js.find("Surface") != js.end())
	{
		for (auto& tile : js["Surface"]) {
			uShort id = tile["Id"].get<uShort>();
			std::string name = tile["Name"].get<std::string>();
			std::string fileLoc = tile["File"].get<std::string>();

			m_surfaces[id] = std::make_pair(name.c_str(), sf::Texture());
			m_surfaces[id].second.loadFromFile(fileLoc);
		}
	}
}

void TileManager::Draw(sf::RenderWindow * win)
{

	sf::Text txt;
	txt.setFont(*font);
	txt.setFillColor(sf::Color::Black);
	txt.setCharacterSize(15);

	uInt tileID = FindTileByPosition(sf::Mouse::getPosition(*win).x, sf::Mouse::getPosition(*win).y);

	for (uInt i = 0; i < m_shapes.size(); ++i)
	{
		//uShort bId = m_tiles[i].m_backId;
		//uShort sId = m_tiles[i].m_surfId;
		//m_shapes[i].setTexture(&m_backgrounds[bId].second);
		//m_shapes[i].setTexture(&m_surfaces[sId].second);
		//win->draw(m_shapes[i]);

		m_shapes[i].setFillColor(sf::Color::White);


		if (tileID != uIError && i == tileID) {
			m_shapes[i].setFillColor(sf::Color::Yellow);
		}


		win->draw(m_shapes[i]);
		txt.setString(std::to_string(uInt(m_shapes[i].getPosition().x + TILE_W * 0.5f)) + "\n" + std::to_string(uInt(m_shapes[i].getPosition().y + TILE_H * 0.5f)));
		txt.setPosition(m_shapes[i].getPosition().x + TILE_W * 0.25f, m_shapes[i].getPosition().y + TILE_H * 0.25f);
		win->draw(txt);
	}
}
