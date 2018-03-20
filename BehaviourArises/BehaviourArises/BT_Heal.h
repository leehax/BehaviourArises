#pragma once
#include "BT_Leaf.h"

class BT_Heal
	:public BT_Leaf
{
public:
	BT_Heal(std::shared_ptr<BlackBoard> p_BB);
	~BT_Heal();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
};

