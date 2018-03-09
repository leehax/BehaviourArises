#pragma once
#include <vector>
#include "PathFindingAlgorithm.h"
#include <memory>

class IGridMap;

class AStarPath:public PathFindingAlgorithm
{
public:
	AStarPath(IGridMap* p_world);
	~AStarPath();
private:

	std::vector< Tile* > RecursivePathFinding() override;
	std::vector < PathFindNode*> AdjacentNodes(PathFindNode* p_cur) override;
	
};

