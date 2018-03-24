#pragma once
#include "BT_Leaf.h"

class BT_Heal
	:public BT_Leaf
{
public:
	BT_Heal(std::shared_ptr<BlackBoard> p_BB, const std::string p_agentName);
	~BT_Heal();
	BT_State Update() override;

private:
	std::string m_agentName;
};

