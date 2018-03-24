#pragma once
#include "BT_Leaf.h"
class BT_Attack :
	public BT_Leaf
{
public:
	BT_Attack(std::shared_ptr<BlackBoard> p_BB);
	~BT_Attack();
	BT_State Update() override;
};

