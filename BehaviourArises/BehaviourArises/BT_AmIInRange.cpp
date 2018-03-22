#include "stdafx.h"
#include "BT_AmIInRange.h"


BT_AmIInRange::BT_AmIInRange(std::shared_ptr<BlackBoard> p_BB, int p_rangeToCheck) :BT_Leaf(p_BB)
{
	m_rangeToCheck = p_rangeToCheck;
}


BT_AmIInRange::~BT_AmIInRange()
{
	m_rangeToCheck = 0;
}

BT_Node::BT_State BT_AmIInRange::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (Manhattan(m_blackBoard->GetVector2i(m_agent->GetName() + "Position"), m_blackBoard->GetVector2i(m_agent->GetName() + "TargetActionPosition")) <= m_rangeToCheck)
	{
		std::cout << "We are in range\n";
		return BT_State::Success;
	}
	std::cout << "NOT in range\n";
	return BT_State::Failure;
}

