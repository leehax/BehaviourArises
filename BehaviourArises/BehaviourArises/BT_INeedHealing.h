#pragma once
#include "BT_Leaf.h"
class BT_INeedHealing :
	public BT_Leaf
{
public:
	BT_INeedHealing(std::shared_ptr<BlackBoard> p_BB);
	~BT_INeedHealing();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
};

