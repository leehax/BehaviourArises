#pragma once
#include <vector>
#include "PathFindingAlgorithm.h"
#include <memory>

class IGridMap;

class JPSPath:public PathFindingAlgorithm
{
public:
	JPSPath(IGridMap* p_world);
	~JPSPath();

	

private:
	void FindSuccessors(PathFindNode* p_node);
	PathFindNode* Jump(PathFindNode* p_cur, PathFindNode* p_parent);
	std::vector< Tile* > RecursivePathFinding() override;
	std::vector < PathFindNode*> AdjacentNodes(PathFindNode* p_node) override;


};

