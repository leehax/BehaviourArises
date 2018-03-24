#pragma once
#include <map>
#include "Math.h"
#include "Config.h"
#include <memory>
#include "Tile.h"
namespace
{
	//modern c++ randomization

	std::random_device rd;
	std::mt19937 mt(rd());

	inline int RandomInt(const int p_maxExclusive)
	{
		const std::uniform_int_distribution<> dist(0, p_maxExclusive - 1);
		return dist(mt);
	}

	inline int RandomInt(const int p_min, const int p_max)
	{
		const std::uniform_int_distribution<> dist(0, p_max - p_min);
		return dist(mt) + p_min;
	}

	inline bool RandomBool(const double probablity = 0.5)
	{
		const std::bernoulli_distribution dist(probablity);
		return dist(mt);
	}
}
class Tile;
class IGridMap :
	public std::enable_shared_from_this<IGridMap>

{
public:
	virtual ~IGridMap() = default;
	virtual void Initialise() = 0;
	virtual void DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a) = 0;
	virtual void Update(float p_delta) = 0;
	virtual Tile* GetTile(int p_gridX, int p_gridY);
	virtual Tile* GetTile(Vector2<int> p_gridPos);
	std::map<std::pair<int, int>, Tile*> GetTiles() { return m_tiles; };
	virtual void HandleEvent(SDL_Event& p_ev, SDL_Point p_pos)=0;
	virtual Tile* GetRandomTile();
	virtual Vector2<int> GetRandomPosition();
protected:
	std::map<std::pair<int, int>, Tile*> m_tiles;
};

inline Tile* IGridMap::GetTile(int p_gridX, int p_gridY)
{
	if (p_gridX<0 || p_gridX>Config::COLUMNS - 1 || p_gridY<0 || p_gridY>Config::ROWS - 1)
	{
		return nullptr;
	}
	return	m_tiles[std::make_pair(p_gridX, p_gridY)];
}

inline Tile* IGridMap::GetTile(Vector2<int> p_gridPos)
{
	if (p_gridPos.x<0 || p_gridPos.x>Config::COLUMNS - 1 || p_gridPos.y<0 || p_gridPos.y>Config::ROWS - 1)
	{
		return nullptr;
	}
	return	m_tiles[std::make_pair(p_gridPos.x, p_gridPos.y)];
}

inline Tile* IGridMap::GetRandomTile()
{
	Tile* randomTile = GetTile(RandomInt(Config::COLUMNS), RandomInt(Config::ROWS));
	while (randomTile->IsBlocked())
	{
		randomTile = GetTile(RandomInt(Config::COLUMNS), RandomInt(Config::ROWS));
	}
	return randomTile;
}

inline Vector2<int> IGridMap::GetRandomPosition()
{
	return GetRandomTile()->GetGridPos();
}

