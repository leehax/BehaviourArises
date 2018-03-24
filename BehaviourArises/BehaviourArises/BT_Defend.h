#pragma once
#include "BT_Leaf.h"
class BT_Defend :
	public BT_Leaf
{
public:
	BT_Defend(std::shared_ptr<BlackBoard> p_pBB);
	~BT_Defend();
	BT_State Update() override;
};

