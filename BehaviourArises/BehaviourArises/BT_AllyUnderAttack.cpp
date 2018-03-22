#include "stdafx.h"
#include "BT_AllyUnderAttack.h"


BT_AllyUnderAttack::BT_AllyUnderAttack(std::shared_ptr<BlackBoard> p_BB) : BT_Leaf(p_BB)
{
}


BT_AllyUnderAttack::~BT_AllyUnderAttack()
{
}

BT_Node::BT_State BT_AllyUnderAttack::Update(std::vector<BT_Node*>& p_openNodes)
{
	if(m_blackBoard->GetBool("HealerUnderAttack"))
	{
		std::cout << "Healer is under attack\n";
		m_blackBoard->SetVector2i(m_agent->GetName() + "TargetPosition", m_blackBoard->GetVector2i("EnemyAttackingHealerPosition"));
		m_blackBoard->SetVector2i(m_agent->GetName() + "TargetActionPosition", m_blackBoard->GetVector2i("EnemyAttackingHealerPosition"));
		m_blackBoard->SetAgent(m_agent->GetName() + "TargetAgent",m_blackBoard->GetAgent("EnemyAttackingHealer"));
		return BT_State::Success;
	}
	return BT_State::Failure;
}