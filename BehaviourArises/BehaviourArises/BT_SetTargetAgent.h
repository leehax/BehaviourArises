#pragma once
#include "BlackBoard.h"
#include "BT_Leaf.h"

class BT_SetTargetAgent
	:public BT_Leaf
{
public:
	BT_SetTargetAgent(std::shared_ptr<BlackBoard> p_BB, const std::string p_agentName);
	~BT_SetTargetAgent();
	BT_State Update(std::vector<BT_Node*>& p_openNodes) override;

private:
	std::string m_agentName = "";
};

