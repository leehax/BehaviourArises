#include "stdafx.h"
#include "BT_SetDestination.h"
#include "Agent.h"

BT_SetDestination::BT_SetDestination(std::shared_ptr<BlackBoard> p_BB, Vector2<int> p_pos):BT_Leaf(p_BB)
{
	m_positionToSet = p_pos;
}


BT_SetDestination::~BT_SetDestination()
{
}

BT_Node::BT_State BT_SetDestination::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	m_blackBoard->SetVector2i(m_agent->GetName()+"TargetPosition", m_positionToSet);
	std::cout << "SetDestination Success\n";
	return BT_State::Success;
}
