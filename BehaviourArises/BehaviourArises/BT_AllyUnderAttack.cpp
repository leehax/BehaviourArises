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

BT_Node::BT_State BT_AllyUnderAttack::Update(std::vector<BT_Node*>& p_openNodes)
{
	if(m_blackBoard->GetBool(m_allyName+"UnderAttack"))
	{ 
		std::cout << m_allyName+" is under attack\n";
		//m_blackBoard->SetVector2i(m_agent->GetName() + "TargetPosition", m_blackBoard->GetVector2i("EnemyAttackingHealerPosition"));
		m_blackBoard->SetVector2i(m_agent->GetName() + "TargetActionPosition", m_blackBoard->GetVector2i("EnemyAttackingHealerPosition"));
		//m_blackBoard->SetAgent(m_agent->GetName() + "TargetAgent",m_blackBoard->GetAgent("EnemyAttackingHealer"));
		return BT_State::Success;
	}
	return BT_State::Failure;
}
