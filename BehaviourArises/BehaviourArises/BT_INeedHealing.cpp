#include "stdafx.h"
#include "BT_INeedHealing.h"
#include "Agent.h"

BT_INeedHealing::BT_INeedHealing(std::shared_ptr<BlackBoard> p_BB) : BT_Leaf(p_BB)
{
}


BT_INeedHealing::~BT_INeedHealing()
{
}

BT_Node::BT_State BT_INeedHealing::Update(std::vector<BT_Node*>& p_openNodes)
{
	if(m_blackBoard->GetInt(m_agent->GetName()+"Health")<=50)
	{
		return BT_State::Success;
	}
	return BT_State::Failure;
}
