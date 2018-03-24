#include "stdafx.h"
#include "BT_AmIInRange.h"
#include "Agent.h"

BT_AmIInRange::BT_AmIInRange(std::shared_ptr<BlackBoard> p_BB, int p_rangeToCheck, const std::string p_positionToCheck) :BT_Leaf(p_BB)
{
	m_rangeToCheck = p_rangeToCheck;
	m_positionToCheck = p_positionToCheck;
	
}


BT_AmIInRange::~BT_AmIInRange()
{
	m_rangeToCheck = 0;
}

BT_Node::BT_State BT_AmIInRange::Update()
{
	if (Manhattan(m_blackBoard->GetVector2i(m_agent->GetName() + "Position"), m_blackBoard->GetVector2i(m_positionToCheck)) <= m_rangeToCheck)
	{
		std::cout << m_agent->GetName()+" We are in range\n";
		return BT_State::Success;
	}
	std::cout << m_agent->GetName() + " NOT in range\n";
	return BT_State::Failure;
}

