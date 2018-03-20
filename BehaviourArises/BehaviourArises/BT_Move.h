#pragma once
#include "BT_Leaf.h"
class BT_Move :
	public BT_Leaf
{
public:
	BT_Move(std::shared_ptr<BlackBoard> p_BB);
	~BT_Move();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
};

