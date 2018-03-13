#pragma once

#include <vector>
#include "Math.h"
#include "IGridMap.h"
class Tile;
class SpriteManager;
class DrawManager;
class Sprite;

class IEntity
{
public:
	IEntity();
	virtual ~IEntity();

	virtual void Update(float p_delta)=0;
	virtual void Draw()=0;
	virtual void SetCurTile(Tile* p_tile);
	virtual void SetCurTile(Vector2<int> p_tileCoord);
	virtual Vector2<int> GetGridPos();
	virtual Vector2<int> GetWorldPos();
	virtual Tile* GetCurrentTile();
	virtual std::string GetType();

protected:
	Tile * m_curTile;
	SpriteManager* m_spriteManager;
	DrawManager* m_drawManager;
	Sprite* m_sprite;
	IGridMap* m_world;
	std::string m_type = "";
};

