#pragma once
#include "BT_Leaf.h"
class BT_AllyNeedsHealing :
	public BT_Leaf
{
public:
	BT_AllyNeedsHealing(std::shared_ptr<BlackBoard> p_BB, const std::string p_allyName);
	~BT_AllyNeedsHealing();
	BT_State Update() override;
private:
	std::string m_allyName;
};

