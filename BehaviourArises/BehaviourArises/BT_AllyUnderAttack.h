#pragma once
#include "BT_Leaf.h"
class BT_AllyUnderAttack :
	public BT_Leaf
{
public:
	BT_AllyUnderAttack(std::shared_ptr<BlackBoard> p_BB);
	~BT_AllyUnderAttack();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
};

