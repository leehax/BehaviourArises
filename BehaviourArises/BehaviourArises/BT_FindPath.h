#pragma once
#include "BT_Leaf.h"
class BT_FindPath :
	public BT_Leaf
{
public:
	BT_FindPath(std::shared_ptr<BlackBoard> p_BB);
	~BT_FindPath();
	BT_State Update() override;
};

