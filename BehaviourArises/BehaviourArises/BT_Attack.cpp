#include "stdafx.h"
#include "BT_Attack.h"
#include "Agent.h"

BT_Attack::BT_Attack(std::shared_ptr<BlackBoard> p_BB) :BT_Leaf(p_BB)
{
}


BT_Attack::~BT_Attack()
{
}

BT_Node::BT_State BT_Attack::Update()
{
	
	m_agent->Attack(m_blackBoard->GetAgent(m_agent->GetName() + "TargetAgent"));
	std::cout << "Attacking\n";
	return BT_State::Success;
}
