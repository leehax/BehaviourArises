#include "stdafx.h"
#include "IEntity.h"
#include "Tile.h"

IEntity::IEntity()
{
}


IEntity::~IEntity()
{
}

void IEntity::SetCurTile(Tile* p_tile)
{
	m_curTile = p_tile;
}

Vector2<int> IEntity::GetGridPos()
{
	return m_curTile->GetGridPos();
}

Vector2<int> IEntity::GetWorldPos()
{
	return m_curTile->GetWorldPos();
}

Tile* IEntity::GetCurrentTile()
{
	return m_curTile;
}

std::string IEntity::GetType()
{
	return m_type;
}
