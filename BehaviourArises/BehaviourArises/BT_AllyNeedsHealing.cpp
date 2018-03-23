#include "stdafx.h"
#include "BT_AllyNeedsHealing.h"
#include "Agent.h"

BT_AllyNeedsHealing::BT_AllyNeedsHealing(std::shared_ptr<BlackBoard> p_BB) :BT_Leaf(p_BB)
{
}


BT_AllyNeedsHealing::~BT_AllyNeedsHealing()
{
}

BT_Node::BT_State BT_AllyNeedsHealing::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	if(m_blackBoard->GetInt("TankHealth")<=50)
	{
		std::cout << "Tank Needs Healing\n";
		//m_blackBoard->SetVector2i(m_agent->GetName()+"TargetLocation", m_blackBoard->GetVector2i("TankPosition"));
		m_blackBoard->SetVector2i(m_agent->GetName() + "TargetActionPosition", m_blackBoard->GetVector2i("TankPosition"));
		return BT_State::Success;
	}
	return BT_State::Failure;
}
