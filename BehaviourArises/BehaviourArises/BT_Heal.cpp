#include "stdafx.h"
#include "BT_Heal.h"


BT_Heal::BT_Heal(std::shared_ptr<BlackBoard> p_BB, const std::string p_agentName): BT_Leaf(p_BB)
{
	m_agentName = p_agentName;
}


BT_Heal::~BT_Heal()
{
}

BT_Node::BT_State BT_Heal::Update()
{
	

	std::cout << "Healing\n";
	m_blackBoard->SetInt(m_agentName+"Health", 100);
	return BT_State::Success;
}
