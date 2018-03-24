#include "stdafx.h"
#include "BT_FindPath.h"
#include "Agent.h"

BT_FindPath::BT_FindPath(std::shared_ptr<BlackBoard> p_BB):BT_Leaf(p_BB)
{
}


BT_FindPath::~BT_FindPath()
{
}

BT_Node::BT_State BT_FindPath::Update()
{
	
	m_agent->ClearPath();
	if (m_agent->FindPath(m_blackBoard->GetVector2i(m_agent->GetName() + "TargetPosition")))
	{
		std::cout << m_agent->GetName()+" FindPath Success\n";
		return BT_State::Success;
	}

	std::cout << m_agent->GetName() + "FindPath Fail\n";
	return BT_State::Failure;
}
