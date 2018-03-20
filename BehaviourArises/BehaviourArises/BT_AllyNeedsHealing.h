#pragma once
#include "BT_Leaf.h"
class BT_AllyNeedsHealing :
	public BT_Leaf
{
public:
	BT_AllyNeedsHealing(std::shared_ptr<BlackBoard> p_BB);
	~BT_AllyNeedsHealing();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
};

