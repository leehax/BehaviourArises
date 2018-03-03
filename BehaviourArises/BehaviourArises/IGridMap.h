#pragma once
#include <map>
#include "Math.h"
class Tile;
class IGridMap 

{
public:
	virtual ~IGridMap() = default;
	virtual void Initialise() = 0;
	virtual void DrawGrid(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a) = 0;
	virtual void Update(float p_delta)=0;
	virtual Tile* GetTile(int p_gridX, int p_gridY)=0;
	virtual Tile* GetTile(Vector2<int> p_gridPos) = 0;
	virtual void HandleEvent(SDL_Event& p_ev, SDL_Point p_pos)=0;
protected:
	std::map<std::pair<int, int>, Tile*> m_tiles;
};

