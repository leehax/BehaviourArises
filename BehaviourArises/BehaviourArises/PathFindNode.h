#pragma once
#include <memory>
#include "Math.h"
class Tile;
class PathFindNode
{
public:
	PathFindNode(Tile* p_tile);
	~PathFindNode();

	unsigned int GetFCost(bool p_considerTerrain);
	unsigned int m_gCost = 0; //travel/accumulated cost
	unsigned int m_hCost = 0; //heuristic cost
	unsigned int TypeModifier();

	Tile* m_tile = nullptr;
	PathFindNode* m_parentNode= nullptr;

	Vector2<int> GetGridPos();
	bool m_blocked(); //get m_tile blocked
};

