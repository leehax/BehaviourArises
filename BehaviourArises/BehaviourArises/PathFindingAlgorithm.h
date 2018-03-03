#pragma once
#include <vector>
#include <map>
#include "Math.h"
class Tile;
class PathFindNode;
class DrawManager;

class PathFindingAlgorithm
{
public:

	virtual std::vector<Tile*> FindPath(Tile* p_currentTile, Tile* p_targetTile);
	virtual void Recalculate();
	virtual void Draw();

protected:
	virtual void Initialize(Tile* p_currentTile, Tile* p_targetTile);
	virtual PathFindNode* GetNodeAt(Vector2<int> p_gridPos);
	virtual PathFindNode* GetNodeAt(int p_gridX, int p_gridY);
	virtual bool BlockedNodeAt(Vector2<int> p_gridPos);
	virtual bool BlockedNodeAt(int p_gridX, int p_gridY);

	virtual std::vector< Tile* > RecursivePathFinding() = 0;
	virtual std::vector < PathFindNode*> AdjacentNodes(PathFindNode* p_cur) = 0;

	bool m_initialized = false;
	std::vector< Tile* > m_tilesInPath;

	PathFindNode* m_startingNode;
	PathFindNode* m_currentNode;
	PathFindNode* m_goalNode;

	std::map<std::pair<int, int>, PathFindNode*> m_nodes;

	std::vector < PathFindNode*> m_openNodes;
	std::vector < PathFindNode*> m_closedNodes;
	std::vector < PathFindNode*> m_nodesInPath;
	

	DrawManager* m_drawManager;
};

