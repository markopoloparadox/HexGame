#pragma once
#include <memory>
#include <SFML\Graphics\ConvexShape.hpp>

#include "Common.h"

class Tile
{
	friend class TileManager;
public:
	Tile() {};
	~Tile() {};

private:
	uInt m_shapeId = 0;

	uShort m_backId = 0;
	uShort m_rescId = 0;

	uShort m_r = 0;
	uShort m_c = 0;
};

