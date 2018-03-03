#include "stdafx.h"
#include "PathFindNode.h"
#include "Tile.h"

PathFindNode::PathFindNode(Tile* p_tile)
{
	m_tile = p_tile;
}


PathFindNode::~PathFindNode()
{
}

unsigned int PathFindNode::GetFCost(bool p_considerTerrain)
{
	if (p_considerTerrain) {
		return m_gCost + m_hCost + TypeModifier();
	}
	return m_gCost + m_hCost;
}

unsigned int PathFindNode::TypeModifier()
{
	return m_tile->m_type * 20;
}

Vector2<int> PathFindNode::GetGridPos()
{
	return m_tile->GetGridPos();
}

bool PathFindNode::m_blocked()
{
	return m_tile->IsBlocked();
}
