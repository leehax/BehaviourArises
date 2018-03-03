#pragma once
#include <vector>
#include "PathFindingAlgorithm.h"

class World;

class AStarPath:public PathFindingAlgorithm
{
public:
	AStarPath(World* p_world);
	~AStarPath();
private:

	std::vector< Tile* > RecursivePathFinding() override;
	std::vector < PathFindNode*> AdjacentNodes(PathFindNode* p_cur) override;
	
};

