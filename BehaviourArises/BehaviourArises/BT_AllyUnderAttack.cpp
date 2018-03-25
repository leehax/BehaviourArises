#include "stdafx.h"
#include "BT_AllyUnderAttack.h"
#include "Agent.h"

BT_AllyUnderAttack::BT_AllyUnderAttack(std::shared_ptr<BlackBoard> p_BB, const std::string p_allyName) : BT_Leaf(p_BB)
{
	m_allyName = p_allyName;
}


BT_AllyUnderAttack::~BT_AllyUnderAttack()
{
}

BT_Node::BT_State BT_AllyUnderAttack::Update()
{
	if(m_blackBoard->GetBool(m_allyName+"UnderAttack"))
	{
		return BT_State::Success;
	}
	return BT_State::Failure;
}
