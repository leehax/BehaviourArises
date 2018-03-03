#include "stdafx.h"
#include "PathFindingAlgorithm.h"
#include "Config.h"
#include "PathFindNode.h"
#include "DrawManager.h"
#include "Tile.h"
std::vector<Tile*> PathFindingAlgorithm::FindPath(Tile* p_currentTile, Tile* p_targetTile)
{
	if (!m_initialized)
	{
		Initialize(p_currentTile, p_targetTile);
		m_currentNode = m_startingNode;
	}

	return RecursivePathFinding();
}

void PathFindingAlgorithm::Recalculate()
{
	m_initialized = false;
}

void PathFindingAlgorithm::Draw()
{
	if (m_initialized) {

		for (auto c : m_closedNodes) {
			m_drawManager->DrawRect(*c->m_tile->GetRect(), 255, 0, 0, 255);


		}
		for (auto o : m_openNodes) {
			m_drawManager->DrawRect(*o->m_tile->GetRect(), 0, 255, 0, 255);


		}

		for (auto n : m_nodesInPath)
		{
			if (n->m_parentNode) {
				m_drawManager->DrawLine(n->m_tile->GetWorldPos().x + Config::HALF_TILE, n->m_tile->GetWorldPos().y + Config::HALF_TILE, n->m_parentNode->m_tile->GetWorldPos().x + Config::HALF_TILE, n->m_parentNode->m_tile->GetWorldPos().y + Config::HALF_TILE, 0, 255, 255, 255);
			}
		}
		m_drawManager->DrawRect(*m_currentNode->m_tile->GetRect(), 255, 255, 0, 255);
	}
}

void PathFindingAlgorithm::Initialize(Tile* p_currentTile, Tile* p_targetTile)
{
	//clear vectors
	for (auto n : m_nodes)
	{
		n.second->m_parentNode = nullptr;
	}
	m_openNodes.clear();

	m_closedNodes.clear();

	m_tilesInPath.clear();

	m_nodesInPath.clear();


	//set starting and goal nodes
	for (auto n : m_nodes)
	{
		if (n.second->m_tile == p_currentTile)
		{
			m_startingNode = n.second;
		}
		if (n.second->m_tile == p_targetTile)
		{
			m_goalNode = n.second;
		}
	}

	m_startingNode->m_gCost = 0;
	m_startingNode->m_hCost = Manhattan(m_startingNode->m_tile->GetGridPos(), m_goalNode->m_tile->GetGridPos());
	m_startingNode->m_parentNode = nullptr;

	m_openNodes.push_back(m_startingNode);

	m_initialized = true;
}

PathFindNode* PathFindingAlgorithm::GetNodeAt(Vector2<int> p_gridPos)
{
	if (p_gridPos.x<0 || p_gridPos.x>Config::COLUMNS - 1 || p_gridPos.y<0 || p_gridPos.y>Config::ROWS - 1)
	{
		return nullptr;
	}
	return	m_nodes[std::make_pair(p_gridPos.x, p_gridPos.y)];

}

PathFindNode* PathFindingAlgorithm::GetNodeAt(int p_gridX, int p_gridY)
{
	if (p_gridX<0 || p_gridX>Config::COLUMNS - 1 || p_gridY<0 || p_gridY>Config::ROWS - 1)
	{
		return nullptr;
	}
	return	m_nodes[std::make_pair(p_gridX, p_gridY)];
}

bool PathFindingAlgorithm::BlockedNodeAt(Vector2<int> p_gridPos)
{
	if (GetNodeAt(p_gridPos) && GetNodeAt(p_gridPos)->m_blocked())
	{
		return true;
	}
	return false;
}

bool PathFindingAlgorithm::BlockedNodeAt(int p_gridX, int p_gridY)
{
	if ((GetNodeAt(p_gridX, p_gridY) && GetNodeAt(p_gridX, p_gridY)->m_blocked()) || GetNodeAt(p_gridX, p_gridY) == nullptr)
	{
		return true;
	}

	return false;
}
