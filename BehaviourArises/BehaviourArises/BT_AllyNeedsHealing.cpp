#include "stdafx.h"
#include "BT_AllyNeedsHealing.h"
#include "Agent.h"

BT_AllyNeedsHealing::BT_AllyNeedsHealing(std::shared_ptr<BlackBoard> p_BB, const std::string p_allyName) :BT_Leaf(p_BB)
{
	m_allyName = p_allyName;
}


BT_AllyNeedsHealing::~BT_AllyNeedsHealing()
{
}

BT_Node::BT_State BT_AllyNeedsHealing::Update()
{


	if(m_blackBoard->GetInt(m_allyName+"Health")<=50)
	{
		return BT_State::Success;
	}
	return BT_State::Failure;
}
