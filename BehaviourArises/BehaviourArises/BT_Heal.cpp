#include "stdafx.h"
#include "BT_Heal.h"


BT_Heal::BT_Heal(std::shared_ptr<BlackBoard> p_BB): BT_Leaf(p_BB)
{
}


BT_Heal::~BT_Heal()
{
}

BT_Node::BT_State BT_Heal::Update(std::vector<BT_Node*>& p_openNodes)
{
	if (std::find(p_openNodes.begin(), p_openNodes.end(), this) != p_openNodes.end())
	{
		//we are already in the opennodes;
	}
	else
	{
		p_openNodes.push_back(this);
	}

	std::cout << "Healing\n";
	m_blackBoard->SetInt("TankHealth", 100);
	return BT_State::Success;
}
