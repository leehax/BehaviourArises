#pragma once
#include "BT_Leaf.h"
class BT_AmIInRange :
	public BT_Leaf
{
public:
	BT_AmIInRange(std::shared_ptr<BlackBoard> p_BB, int p_rangeToCheck);
	~BT_AmIInRange();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;
	int m_rangeToCheck = 0;
};

