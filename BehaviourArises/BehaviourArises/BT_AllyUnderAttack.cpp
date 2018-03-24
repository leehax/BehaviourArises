#include "stdafx.h"
#include "BT_AllyUnderAttack.h"
#include "Agent.h"

BT_AllyUnderAttack::BT_AllyUnderAttack(std::shared_ptr<BlackBoard> p_BB, const std::string p_allyName) : BT_Leaf(p_BB)
{
	m_allyName = p_allyName;
}


BT_AllyUnderAttack::~BT_AllyUnderAttack()
{
}

BT_Node::BT_State BT_AllyUnderAttack::Update()
{
	if(m_blackBoard->GetBool(m_allyName+"UnderAttack"))
	{ 
		std::cout << m_allyName+" is under attack\n";
	//	m_blackBoard->SetVector2i(m_agent->GetName() + "TargetEnemy", m_blackBoard->GetVector2i("EnemyAttacking"+m_allyName+"Position"));
		return BT_State::Success;
	}
	return BT_State::Failure;
}
