#include "stdafx.h"
#include "BT_FindPath.h"


BT_FindPath::BT_FindPath(std::shared_ptr<BlackBoard> p_BB):BT_Leaf(p_BB)
{
}


BT_FindPath::~BT_FindPath()
{
}

BT_Node::BT_State BT_FindPath::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	m_agent->ClearPath();
	if (m_agent->FindPath(m_blackBoard->GetVector2i(m_agent->GetName() + "TargetPosition")))
	{
		std::cout << "FindPath Success\n";
		return BT_State::Success;
	}

	std::cout << "FindPath Fail\n";
	return BT_State::Failure;
}
