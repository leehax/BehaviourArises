#include "stdafx.h"
#include "BT_SetDestination.h"


BT_SetDestination::BT_SetDestination(std::shared_ptr<BlackBoard> p_BB):BT_Leaf(p_BB)
{
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

	m_blackBoard->SetVector2i("TargetPosition", m_blackBoard->GetVector2i("WoundedAlly"));
	std::cout << "SetDestination Success\n";
	return BT_State::Success;
}
