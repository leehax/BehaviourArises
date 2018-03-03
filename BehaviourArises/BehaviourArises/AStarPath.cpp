#include "stdafx.h"
#include "AStarPath.h"
#include "PathFindNode.h"
#include "Tile.h"
#include "World.h"
#include "ServiceLocator.h"
#include "DrawManager.h"
#include <algorithm>
#include <iostream>

AStarPath::AStarPath(World* p_world)
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	//Create a node at each tile in the world
	for(auto t: p_world->GetTiles())
	{
		m_nodes.insert(std::pair<std::pair<int,int>,PathFindNode*>(t.first, new PathFindNode(t.second)));
	}

	m_initialized = false;
}


AStarPath::~AStarPath()
{
	for (auto m : m_nodes)
	{
		m.second->m_tile = nullptr;
		delete m.second;
		m.second = nullptr;
	}
	m_nodes.clear();
	m_openNodes.clear();
	m_closedNodes.clear();
	m_tilesInPath.clear();

	m_goalNode = nullptr;
	m_startingNode = nullptr;
	
}


std::vector< Tile* > AStarPath::RecursivePathFinding()
{

	if (m_currentNode == m_goalNode)
	{
		//set the current node's parent to the goal's parent for readability in the following for loop
		m_goalNode->m_parentNode = m_currentNode->m_parentNode;

		//build and return path
		for(PathFindNode * path = m_goalNode; path!=nullptr; path=path->m_parentNode)
		{
			m_nodesInPath.push_back(path);
			m_tilesInPath.push_back(path->m_tile);
		}
		return m_tilesInPath;
		
	}

	else {
		unsigned int lowestF = UINT_MAX;
		int nodeIndex = -1;
		//init adjacent node variables and add the nodes to the open list
		for (auto a: AdjacentNodes(m_currentNode))
		{
			
			bool nodeInOpenOrClosedList = std::find(m_openNodes.begin(), m_openNodes.end(), a) != m_openNodes.end() || std::find(m_closedNodes.begin(), m_closedNodes.end(), a) != m_closedNodes.end();
			if (a->m_tile->IsBlocked() == false && !nodeInOpenOrClosedList)
			{

				a->m_parentNode = m_currentNode;
				//check if the node is adjacent orthogonally or diagonally by checking the manhattan dist, 1=ortho, 2=diagonal
				if(Manhattan(m_currentNode->m_tile->GetGridPos(), a->m_tile->GetGridPos())==1)
				{
					a->m_gCost = m_currentNode->m_gCost + 10;
				}
				else if (Manhattan(m_currentNode->m_tile->GetGridPos(), a->m_tile->GetGridPos()) == 2)
				{
					a->m_gCost = m_currentNode->m_gCost + 14;
				}

				
				a->m_hCost = Manhattan(a->m_tile->GetGridPos(), m_goalNode->m_tile->GetGridPos())*10;
				m_openNodes.push_back(a);
			}
			
		}
		//move current to closed list
		m_closedNodes.push_back(m_currentNode);
		m_openNodes.erase(std::remove(m_openNodes.begin(), m_openNodes.end(), m_currentNode), m_openNodes.end());

		if (m_openNodes.empty() == false) {

			//loop open list, select node with lowest F
			for (unsigned int i = 0; i < m_openNodes.size(); i++)
			{
				if (m_openNodes[i]->GetFCost(true) < lowestF)
				{
					lowestF = m_openNodes[i]->GetFCost(true);
					nodeIndex = i;
				}
			}

			//set current to best node
			m_currentNode = m_openNodes[nodeIndex];

			//recurse
			return RecursivePathFinding();
		}
		//no valid path found to target
		return {};
	}
}

std::vector<PathFindNode*> AStarPath::AdjacentNodes(PathFindNode* p_cur)
{
	std::vector<PathFindNode*> adjacentNodes;

	//Orthogonally adjacent
	if(p_cur->m_tile->GetGridPos().x> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y)]);
	}
	if (p_cur->m_tile->GetGridPos().x< Config::COLUMNS-1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y)]);
	}
	if (p_cur->m_tile->GetGridPos().y> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x , p_cur->m_tile->GetGridPos().y-1)]);
	}
	if (p_cur->m_tile->GetGridPos().y< Config::ROWS - 1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x, p_cur->m_tile->GetGridPos().y+1)]);
	}

	//Diagonally adjacent
	if (p_cur->m_tile->GetGridPos().x> 0 && p_cur->m_tile->GetGridPos().y> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y-1)]);
	}
	if (p_cur->m_tile->GetGridPos().x> 0 && p_cur->m_tile->GetGridPos().y< Config::ROWS - 1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x - 1, p_cur->m_tile->GetGridPos().y + 1)]);
	}
	if (p_cur->m_tile->GetGridPos().x< Config::COLUMNS - 1 && p_cur->m_tile->GetGridPos().y> 0)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y - 1)]);
	}
	if (p_cur->m_tile->GetGridPos().x< Config::COLUMNS - 1 && p_cur->m_tile->GetGridPos().y< Config::ROWS - 1)
	{
		adjacentNodes.push_back(m_nodes[std::make_pair(p_cur->m_tile->GetGridPos().x + 1, p_cur->m_tile->GetGridPos().y+1)]);
	}
	
	return adjacentNodes;
}
